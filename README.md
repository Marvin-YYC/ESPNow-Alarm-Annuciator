# ESPNow-Alarm-Annuciator
Alarm system using ESP now on Seeed Xiao ESP32c3

This code does not currently include the **Initiator** code from the other ESP32 as I am still having trouble figuring out how to get it to work with the XIAO board. 
Once I have that sorted out and the solar charged battery I will add it here. I can only get it to run on a WROOM.

The way it is currently running, the **Initiator** board in the garage or at a remote gate/building sends a data message to the **Annunciator** board which is located 
in my house. When the message indicates that a door/gate is open it activates a buzzer and Red LED on the **Annunciator** and then connects to wifi and sends a message
to CallMeBot.  CallMeBot in turn sends a message to my phone through Signal Message App & API (CallMeBot also works with WhatsApp and Telegram).
At the moment the message is sent correctly (less than 10 seconds) but the Annunciator does not return to normal state when doors are closed. It hangs up at line 43. 
A normal state (door closed) is indicated by a slow flash (30 sec) Green LED
An alarm state (door open) is indicated by a fast flash (1 sec) Red LED with buzzer along with notificaiton from CallMeBot
There is also a Blue LED that goes High when there is an error code from CallMeBot.
When the Door closes Green LED goes High (slow flash) and Red LED goes Low.

I would also like to have the system send a door closed message and a start-up message, but will have to work that out later.
