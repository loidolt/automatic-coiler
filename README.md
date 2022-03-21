# Automatic Coiler

## Summary
This is an automatic winding machine for coiling up small cords, strings, or wires. We needed a way to reliably coil up specific lengths of cord for sale in a kit. This machine is the updated version of my original Automatic Winding Machine, making it more reliable, easier to use, and above all much, much quieter.

The rotary encoder keeps track of the distance coiled with a closed-loop system. This allows more foolproof operation, recovery if the spool hangs up or jams, and the ability to adjust the diameter of the coil without having to change the code.

This version features an LCD display with button controls, easy to edit firmware, more robust encoder guide system, an integrated spool holder, a quiet belt-driven platter, enclosed electronics, and a ton of other tiny tweaks and improvements.

Let me know if you have any questions or need build instructions. I'm happy to provide more detail but will need time to do the full instructional write-up. I can also provide pre-built custom acrylic panels and aluminum plates on request for a small fee.

Happy building!

## Print Settings
### Resolution:
.3

### Infill:
50

### Filament_material:
PLA or PETG

### Notes:
Print the Guide Wheels and Idler Wheel at high resolution, I used 0.1 mm layer height and 3 perimeters.

Print the Plate Shaft Mount solid (100% infill) to ensure it is nice and rigid.

## Bill of Materials
### Hardware
2020 Misumi T-Slot:
- 16x 260mm
- 4x 450mm

Lots of Cast Aluminum Corner Brackets (or print some if you want plastic brackets)

#### Tubing and Shafts:
- 1x 8mm x 75mm Round Metal Rod
- 2x 16mm OD x 215mm Round Aluminum Tube

#### Bearings:
18x 623Z Flange Bearing
2x 608Z

#### Fasteners:
- 4x M8-1.25 x 16mm Button Head Hex Socket Cap Screws
- A bunch of M4 screws, washers, and t-slot nuts

#### Other:
- M3 x 50mm Round Aluminum Standoff
- 1/4" x 12" Aluminum 5052 Plate Disk
- 2x 12"x12" White Acrylic Sheet

### Electronics
#### Mechanical:
- 1x Signswise 600p/r Incremental Rotary Encoder Dc5-24v Wide Voltage Power Supply 6mm Shaft
- 1x Greartisan DC 12V 200RPM Gear Motor High Torque
- 1x GT2 Pulley 20 Teeth 6mm Bore
- 1x GT2 Pulley 60 Teeth 8mm Bore
- 1x GT2 158mm Timing Belt Closed Loop
- 1x 10A 250V AC Inlet with Rocker Switch
- 1x Panel Mount USB Cable B to B

#### Control:
- 1x L298N Motor Drive
- 1x Arduino Nano
- 1x 16x2 LCD
- 2x 40mm Fan
- 1x 120v to 12v Power Supply (5-10 amp depending on your motor choice)
- 4x Arcade Buttons