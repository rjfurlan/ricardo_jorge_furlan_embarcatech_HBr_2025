# ⚠ Disclaimer
# THE SOFTWARE IS PROVIDED "AS IS", USE AT YOUR OWN RISK
# O SOFTWARE É FORNECIDO "COMO ESTÁ", USE POR SUA CONTA E RISCO
 
### This code was developed for educational purposes as a task for phase 2, residency, of the EmbarcaTech professional training program, with the aim of demonstrating some points learned during the residency.

## The goal of this exercise is to create a concept application with a simple hello word, but which has automated testing routines for some functions.


### To change the program between **normal mode and test mode**

Change the line in the CMakeLists.txt file:  
**set(TEST OFF)**  
to  
**set(TEST ON)**

### Code structure

    /project-root
    ├── app/
    │   ├── main.c
    │   ├── func.c
    │   └── func.h
    ├── test/
    │   ├── test_func.c
    │   ├── unity.c
    │   ├── unity.h
    │   └── unity_internals.h
    ├── CMakeLists.txt
    └── pico_sdk_import.cmake

Obs.: unity.c and unity.h were copied from the Unity-2.6.1/src direct of the https://github.com/ThrowTheSwitch/Unity/archive/refs/tags/v2.6.1.tar.gz

Description:
    -  main.c → código principal quando não estiver testando
    - func.c/.h → funções que você quer testar
    - test/test_func.c → testes usando Unity, chamando as funções do func.c
    - CMakeLists.txt → com opção de build normal ou build para testes (podemos usar uma flag tipo -DTEST=1)    


### Temperature

| Temperature (Celsius) | AD Value |
| --- | --- |
| -50 | 1041 |
| -20 |  975 |
| -10 |  954 |
|   0 |  933 |
|  20 |  890 |
|  25 |  879 |
|  27 |  875 |
|  50 |  826 |
|  80 |  762 |
| 100 |  719 |
| 120 |  676 |
| 150 |  613 |

 
AD_value = (((27 - Tcelsius) * 0.001721) + 0.706) * 4095 / 3.3

Tcelsius = 27 - (((AD_value * 3.3 / 4095) - 0.706) / 0.001721);


## References
#### Unity
Site oficial: https://www.throwtheswitch.org/unity  
GitHub: https://github.com/ThrowTheSwitch/Unity  

#### Downloaded version
https://github.com/ThrowTheSwitch/Unity/releases/tag/v2.6.1  
https://github.com/ThrowTheSwitch/Unity/archive/refs/tags/v2.6.1.tar.gz  