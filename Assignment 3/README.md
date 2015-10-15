#Assignment 3 - Designing a case using 3D printing and laser cutting

This repo contains the files and details on building a case for the circuit made in <a href="https://github.com/DhananjaiH/HCIN720-Fall15/tree/master/Assignment%202/Cloud">Assignment 2</a>.

<b>Preparation</b><br>
In order to make a nice compact case for the circuit in assignment 2, the circuit itself needs some soldering so that it is nice and compact.

Here is an image of the soldered circuit.
<img src="https://raw.githubusercontent.com/DhananjaiH/HCIN720-Fall15/master/Assignment%203/IMG_20151015_131533.jpg">
<br>What I was trying to achieve here was to elevate the i/o elements (7-segment display, potentiometer, switch and the IR proximity sensor) so that they would be slightly higher than the photon. This way, only those components would be exposed outside the box.

<pre>
	<b><i>Lessons learnt:</i></b>
	Here are some things that I learnt from this activity.
	<li>The above circuit, while small and seems to be easily adjustable, the design leaves it too exposed. 
		This makes the wire joints vulnerable to damage and easy to break. 
		(As I learnt when I accidentally broke a wire joint on the proximity sensor, rendering it useless.)</li>
	<li>Design the final soldered circuit such that the vulnerable wires are protected from damage and do not move much.</li>
</pre>

<b>3D printing</b><br>
Given the nature of the circuit in Assignment 2, 3D printing a case seemed to be the best approach.

The 'case_base_3Dprint.obj' and 'case_lid_3Dprint.stl' were the designs used for this. Below are images that show each of these printed objects.
<img src="https://raw.githubusercontent.com/DhananjaiH/HCIN720-Fall15/master/Assignment%203/IMG_20151015_131111.jpg">

Base<br>
I designed the case bottom-up, starting the with the base, or the 'box' part.

The box design is fairly simple and straight-forward. Made using <a href="https://www.tinkercad.com/">Tinkercad</a>, I made the use of wedges to act as support structures. These are used for the 2 screw holes. A large wedge is also added for resting the proximity sensor on this platform.

Lid<br>
I chose to make the lid using <a href="http://www.123dapp.com/design">123D Design</a> as it offers some more complex functionality for 3D design. This was helpful in aligning the screws to the screw-holes made in the base. The design includes appropriate holes for various components.

Here is the complete box.
<img src="https://raw.githubusercontent.com/DhananjaiH/HCIN720-Fall15/master/Assignment%203/IMG_20151015_131301.jpg">

<b>Laser Cutting</b><br>
I also made a design ('cardboard_case_lasercutter.svg') for a box to be made out of laser cut cardboard pieces. I made use of an old used cardboard box. However, due to the nature of cardboard, it is not strong or robust enough for this purpose. Laser cut wood pieces would make for more suitable material for the case.