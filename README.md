# Zephyr Template Project

This project acts as a starting point for creating a new Zephyr RTOS application, with various configurations pre-set in a convenient manner.

## Building from a Fresh Clone

```bash
# initialize the west repo
west init -l mainfest

# update the west repo
west update

# install python dependencies (from within virtualenv)
pip install -r zephyr/scripts/requirements

# building the sample code
west build -b=nucleo_l452re app
```

## Configuring this Repo

This repo is marked with 'TEMPLATE_CONFIG' comments anywhere it is expected that a user would want to change a configuration before the first build.
