# ESPNow-Alarm-Annuciator
Alarm system using ESP now on Seeed Xiao ESP32c3

This code does not currently include the **Initiator** code from the other ESP32 as I am still having trouble figuring out how to get it to work with the XIAO board. 
Once I have that sorted out and the solar charged battery I will add it here. I can only get it to run on a WROOM.

The way it is currently running, the **Initiator** board in the garage or at a remote gate/building sends an *ESP-Now* data message to the **Annunciator** board which is located in my house. 
When the *ESP-Now* message indicates that a door/gate is open it activates a buzzer and a Red LED on the **Annunciator** is illuminated.  It then connects to WiFi and sends a message to CallMeBot.  CallMeBot in turn sends a message to my phone through the *Signal Message App* via API (CallMeBot also works with WhatsApp and Telegram).  After 500sec (8.33 min) it sends the door open message again if the door is not closed.
At the moment the message is sent correctly (usually less than 5 seconds) but the Annunciator does not return to its normal state when doors are closed. It hangs up at line 43. 

■ I wanted something that would make and audible alarm in the house, in the event someone breaks into my garage at night while my phone is asleep  This is why I wanted an **Annunciator** with an alarm, rather than just a ESP32 in the garage that sends a message to CallMeBot.  The project was originally for a friend who is on an acreage, and wanted to know when someone opens his gate, which is a few hundred metres from his home and too far from his wifi.  I was going to use a couple LoRa equipped ESP32 for this, but I haven't gotten that far yet.

Ω Normal Status (door closed) is indicated by a slow flash (30 sec) Green LED

Ω An alarm state (door open) is indicated by a fast flash (1 sec) Red LED with buzzer in sequence w/pause along with notification from CallMeBot. After 500sec (8.33 min) it sends the door open message again if the door is not closed. Or in this case if the board is not reset.

Ω There is also a Blue LED that goes high when there is an error code http response from CallMeBot.

Ω When the Door closes Green LED goes high (slow flash) and Red LED goes low. Green LED shows slow flash all the time. Normal Status.

Ω Blue light should stay high if high when Green or Red, until board reset or http response OK but not sure if it works this way, as it hangs-up.

Ω When the board is powered up it cycles all three LED's in sequence. Blue,Red,Green, to Green -slow flash


☻ I would also like to have the system send a door closed message and a start-up message, but will have to work that out later.

Thanks in advance to anyone that can offer assistance ☺ I'm new to coding and Arduino IDE


