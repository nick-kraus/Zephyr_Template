#include <app_version.h>
#include <zephyr/drivers/gpio.h>
#include <zephyr/kernel.h>
#include <zephyr/logging/log.h>

LOG_MODULE_REGISTER(app, CONFIG_APP_LOG_LEVEL);

static const struct gpio_dt_spec button = GPIO_DT_SPEC_GET(DT_ALIAS(sw0), gpios);
static struct gpio_callback button_cb;

static struct gpio_dt_spec led0 = GPIO_DT_SPEC_GET(DT_ALIAS(led0), gpios);

static uint32_t button_count = 0; 
void button_pressed(const struct device *dev, struct gpio_callback *cb, uint32_t pins) {
	ARG_UNUSED(dev);
	ARG_UNUSED(cb);
	ARG_UNUSED(pins);

	button_count++;
	LOG_INF("button pressed %u times", button_count);
}

int32_t board_setup(void) {
	int32_t ret;

	if (!gpio_is_ready_dt(&button)) {
		LOG_ERR("Button init failed");
		return -ENODEV;
	}
	ret = gpio_pin_configure_dt(&button, GPIO_INPUT);
	if (ret < 0) {
		LOG_ERR("Button configure failed (%d)", ret);
		return ret;
	}
	ret = gpio_pin_interrupt_configure_dt(&button, GPIO_INT_EDGE_TO_ACTIVE);
	if (ret < 0) {
		LOG_ERR("Button irq configure failed (%d)", ret);
		return ret;
	}
	gpio_init_callback(&button_cb, button_pressed, BIT(button.pin));
	gpio_add_callback(button.port, &button_cb);

	if (!gpio_is_ready_dt(&led0)) {
		LOG_ERR("Led0 init failed");
		return -ENODEV;
	}
	ret = gpio_pin_configure_dt(&led0, GPIO_OUTPUT);
	if (ret < 0) {
		LOG_ERR("Led0 configure failed (%d)", ret);
		return ret;
	}

	return 0;
}

int32_t main(void) {
	int32_t ret = board_setup();
	if (ret < 0) {
		return ret;
	}

	LOG_INF("version: %s", STRINGIFY(APP_BUILD_VERSION));

	while (1) {
		/* Switch between LED always on, and blinking, depending on button press. */
		if ((button_count % 2) == 0) {
			gpio_pin_toggle_dt(&led0);
		} else {
			gpio_pin_set_dt(&led0, 1);
		}

		k_msleep(250);
	}

	return 0;
}
