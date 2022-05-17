# StopWatch-embbeded-project
Using Atmega 16 for implementing Stop Watch System with features like ( Pause, Resume &amp; Reset )

Description:

By using atmega 16, 6 seven segment display, only 1 7447 dicoder,
3 push button with different configuration( pull up, pull down), Timer1 with frequency 1hz,
prescalar with Fcpu/1024 and interrupt to impelemt the push buttons.

How it works:

By Pressing start in proteus the StopWatch the counter will start with Hour:Min:Sec
each have two digits.
By pressing PD2 (pull down button) : the counter will reset
By pressing PD3 (pull up button)   : the counter will pause
By pressing PB2 (pull down button) : the counter will resume 
