The Project

For my first anniversary to my lovely wife, I decided to combine traditional and contemporary -- and an affectionate sign of geekiness!

Components

This is an Arduino sketch which was developed on a Pro Mini 5V, connected to a DS3231 Real-Time Clock (RTC), a IS31FL3731 LED controller, and a 16x9 LED display. It is mounted inside a handcrafted (by me) wooden box, and serves as a desk clock.

How It Works

This will assign the sketch's compile-time to the RTC if the RTC has not been recently powered, and updates the displayed time each loop iteration. It is intended to be powered via USB connected to an AC cube, but can survive power outages, moving to different plugs, etc due to the RTC.

Summary

I love you, Sarah!
