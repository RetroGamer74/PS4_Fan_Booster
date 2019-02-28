
# PS4_Fan_Booster
=================

This payload allows to dynamically inject a modification on the current payload binary as parameter to change temperature based on payload setup form in the PS4ADMIN payload manager for PS4.

In order to use PS4ADMIN you have to setup your Primary and Secondary DNS to the IP: 139.99.172.148

When done you can launch the User Guide. Once in the PS4ADMIN website select the latest option menu which is Store PS4ADMIN in Cache.

When finished, wait for PS4ADMIN to reload the page, and then go to Homebrew Menu and select Fan Booster.

In the Exploit Customization tab, you will be able to choose the desired temp.

Remember this temp is a threshold. It means at what temp the fan will start to work. So don't become crazy and take care.

This payload has to be used with PS4ADMIN. If you use it by itself (PS4-fan-control.bin) the default TEMP ( 60 Celsius Degrees ) will be used always.

You need the PS4ADMIN website to inject the param to the payload.

Use this at your own risk. No resposabilities from my side.

Credits
=======

This payload is an improvement based on the information about PS4 fan from Zer0xFF  https://gist.github.com/Zer0xFF/4aa38d836a5696ed1b6486bb8e782b4a and the project on https://github.com/ethylamine/PS4-fan-control

