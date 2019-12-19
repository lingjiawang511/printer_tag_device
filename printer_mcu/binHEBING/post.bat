del ..\printer_mcu_link.bin
fsutil  file createnew ..\printer_mcu_link.bin 16384
..\binHEBING\cat ..\printer_mcu_app.bin >>..\printer_mcu_link.bin
..\binHEBING\hbin ..\binHEBING\STM32F1xx_IAP.bin ..\printer_mcu_link.bin