# Assignment 2 : Interacting with the Photon and visualizing data

This project uses a circuit build with the <a href="https://www.particle.io/">Particle Photon</a> and visualizes data over the cloud through some interactivity.

Check this link <a href="http://rawgit.com/DhananjaiH/HCIN720-Fall15/master/Assignment%202/Cloud/index.html">here</a>. 

<b>Details</b>
<p>This circuit uses the <a href="https://www.particle.io/">Particle Photon</a> in combination with an <a href="https://www.sparkfun.com/products/242">IR proximity sensor(GP2Y0A21YK)</a>, which is used for giving simple gesture inputs. A <a href="https://www.sparkfun.com/products/8546">7-segment display</a> is used to provide some on-circuit visualization of the distance of the users hand from the sensor. 
<br><br>
Here is an image of the of the circuit.
<br>
<img src="https://raw.githubusercontent.com/DhananjaiH/HCIN720-Fall15/master/Assignment%202/Cloud/IMG_20150929_124954.jpg"></img>
<br><br>
The 7-segment display shows the user's hand distance in levels (below)</p>
<pre>
                               _
                 _     |_|    |_|
    _    |_|    |_|    |_|    |_|
</pre>

In order to reliably achieve this, we need to perform some thresholding for the readings from the proximity sensor. The sensor works well between the 10cm - 80cm range. The code for the photon circuit with the IR proximity sensor and 7-segment display can be found in the .ino file. The code for thresholding is also in the same file, within the setup() function.

<li><b>Thresholding</b></li>
For setting the threshold, we first take some readings with the user's hand placed at a comfortable distance above the sensor. The display will show a 5 second countdown to allow the user some time to get ready. This will the distance used for registering an action with the device.

Follwing this, some readings are taken without the user's hand above the sensor. Using these readings, we can now segment the values from the IR proximity sensor into 'zones'.

Once the thresholding is performed, the device is ready to use. When the user's hand crosses the threshold, an 'input' is registered. This input is used for controlling a simple game - the 2D Dinosaur side scroller game available on Chrome browsers when there is not internet connectivity. <a href="https://github.com/CloudCannon/Dinosaur-Chrome-Game">Here</a> is a really nice imitation of the game that was used for this. When an 'input' is registered with the device, it sends this information to the Particle cloud. The game runs on the Server-Sent Events from this cloud.

NOTE: Of course, this only works for my device and you will have to change this for your use.

<b>Challenges</b>
<p>The IR proximity sensor only works reliably with a certain amount of ambient lighting present in the surroundings. The thresholding is not very reliable when there is no sufficient lighting. This could theoretically be improved by supplying more infrared lighting (through an array of IR LEDs).

Also, there is a small delay in controlling the game over the cloud, as it takes some time for the input to reach the game. Thus, the game may not react as quickly as you may move your hand.</p>

<b>References:</b>
<p>
<li>Working with server-sent events: <a href="https://developer.mozilla.org/en-US/docs/Web/API/Server-sent_events/Using_server-sent_events">link</a></li>
<li><a href="https://github.com/CloudCannon/Dinosaur-Chrome-Game">Google Chrome Dinosaur game</a></li>
<li>Working with the IR proximity sensor: <a href="http://bildr.org/2011/03/various-proximity-sensors-arduino/">link</a></li>
</p>