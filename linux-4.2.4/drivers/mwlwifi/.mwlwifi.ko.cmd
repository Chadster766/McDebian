cmd_drivers/mwlwifi/mwlwifi.ko := arm-none-eabi-ld -EL -r  -T ./scripts/module-common.lds --build-id  -o drivers/mwlwifi/mwlwifi.ko drivers/mwlwifi/mwlwifi.o drivers/mwlwifi/mwlwifi.mod.o
