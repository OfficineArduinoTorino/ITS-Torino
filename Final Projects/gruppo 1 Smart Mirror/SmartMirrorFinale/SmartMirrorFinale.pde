// Run this program only in the Java mode inside the IDE,
// not on Processing.js (web mode)!!

import processing.video.*;
import com.temboo.core.*;
import com.onformative.yahooweather.*;
import com.temboo.Library.Google.Calendar.*;
import com.temboo.Library.Google.Gmail.*;

YahooWeather weather;

TembooSession session = new TembooSession("pollorollorallero", "myFirstApp", "601c20a752224c80b4bfe743ed6d777b");

Capture cam;


int updateIntervallMillis = 120000; 
String s = "meteo"; 
String c ="calendar";
String m = "Mail";
long lastime;
long dtime = 120000;

int screenW = 960;
int screenH = 1706;
float factor = 1.77;

//riconoscimento
int numPixels;
int[] backgroundPixels;
Capture video;

//Clock
int cx, cy;
float secondsRadius;
float minutesRadius;
float hoursRadius;
float clockDiameter;

void setup() {
  size(screenW, screenH);//(720, 1280);
  cam = new Capture(this, 1280, 720, 30);
  cam.start();
  textFont(createFont("Arial", 14));

  weather = new YahooWeather(this, 12591807, "c", updateIntervallMillis);

  lastime = millis();
  weather.update();
   s = ("\nCittà: "+weather.getCityName()
    +"\nRegione: "+weather.getRegionName()
    +"\nPaese: "+weather.getCountryName()
    +"\nAlba: "+weather.getSunrise()
    +"\nTemperatura: "+weather.getTemperature()+"°"
    +"\nUmidità: "+weather.getHumidity()+"%"
    );
  c= calendar();
  m = mail();

//Clock
  int radius = min(200, 200) / 2;
  secondsRadius = radius * 0.72;
  minutesRadius = radius * 0.60;
  hoursRadius = radius * 0.50;
  clockDiameter = radius * 1.8;
  
  cx = 800;
  cy = 200 / 2;

  /*parte di riconoscimento
  video = new Capture(this, width, height);

  // Start capturing the images from the camera
  video.start();  

  numPixels = video.width * video.height;
  // Create array to store the background image
  backgroundPixels = new int[numPixels];
  // Make the pixels[] array available for direct manipulation
  loadPixels();*/
}

String calendar() {

  GetNextEvent getNextEventChoreo = new GetNextEvent(session);

  // Set inputs
  getNextEventChoreo.setClientSecret("dvfHaRVjFfEqII9xfzX-2SPK");
  getNextEventChoreo.setCalendarID("dichio.boris@gmail.com");
  getNextEventChoreo.setRefreshToken("1/93_ZXxlZgkeP65Mxvnj1RzWAUAzSPh2vl9Z0Eg1QvdY");
  getNextEventChoreo.setClientID("953352137736-aom2m01htlc40tn583in1ctjoskqfete.apps.googleusercontent.com");

  // Run the Choreo and store the results
  GetNextEventResultSet getNextEventResults = getNextEventChoreo.run();

  String c = ( "         Prossimo evento   \n\n"+getNextEventResults.getSummary()
    +"\nOra di inizio:  \n"+getNextEventResults.getBeginTime()
    + "\nOra di fine:  \n"+getNextEventResults.getEndTime()
    );

  return (c);
}

String mail() {

  GetUnreadMail getUnreadMailChoreo = new GetUnreadMail(session);

  // Set inputs
  getUnreadMailChoreo.setClientSecret("DOMIc0inlSM8lyGZBK9uXOYp");
  getUnreadMailChoreo.setRefreshToken("1/6X4OQ0p-qm5ut5ft7JIiwJAceiivHWsZ45ii2ZRq1cI");
  getUnreadMailChoreo.setClientID("953352137736-mgu5p27ieun4ahq5j95kiv8o4hag22ri.apps.googleusercontent.com");

  // Run the Choreo and store the results
  GetUnreadMailResultSet getUnreadMailResults = getUnreadMailChoreo.run();

  String m = ( "         Mail non lette   \n\n"
    +"Numero mail non lette:  "+getUnreadMailResults.getFullCount()
    +"\nTesto mail:  \n"+getUnreadMailResults.getResponse()
    );

  return (m);
}
/*
int riconosci() {
  int flag = 0;
  int tmp = 0;
  
   if (video.available()) {
    video.read(); // Read a new video frame
    video.loadPixels(); // Make the pixels of video available
    // Difference between the current frame and the stored background
    int presenceSum = 0;
    for (int i = 0; i < numPixels; i++) { // For each pixel in the video frame...
      // Fetch the current color in that location, and also the color
      // of the background in that spot
      color currColor = video.pixels[i];
      color bkgdColor = backgroundPixels[i];
      // Extract the red, green, and blue components of the current pixel's color
      int currR = (currColor >> 16) & 0xFF;
      int currG = (currColor >> 8) & 0xFF;
      int currB = currColor & 0xFF;
      // Extract the red, green, and blue components of the background pixel's color
      int bkgdR = (bkgdColor >> 16) & 0xFF;
      int bkgdG = (bkgdColor >> 8) & 0xFF;
      int bkgdB = bkgdColor & 0xFF;
      // Compute the difference of the red, green, and blue values
      int diffR = abs(currR - bkgdR);
      int diffG = abs(currG - bkgdG);
      int diffB = abs(currB - bkgdB);
      // Add these differences to the running tally
      presenceSum += diffR + diffG + diffB;
      tmp = presenceSum;
      // Render the difference image to the screen
      pixels[i] = color(diffR, diffG, diffB);
      // The following line does the same thing much faster, but is more technical
      //pixels[i] = 0xFF000000 | (diffR << 16) | (diffG << 8) | diffB;
      
    }
    updatePixels(); // Notify that the pixels[] array has changed
    println(presenceSum); // Print out the total amount of movement
  }
  return(tmp);
}*/

void clock() {
  //background(0);
  
  // Draw the clock background
  noFill();
  noStroke();
  ellipse(cx, cy, clockDiameter, clockDiameter);
  
  // Angles for sin() and cos() start at 3 o'clock;
  // subtract HALF_PI to make them start at the top
  float s = map(second(), 0, 60, 0, TWO_PI) - HALF_PI;
  float m = map(minute() + norm(second(), 0, 60), 0, 60, 0, TWO_PI) - HALF_PI; 
  float h = map(hour() + norm(minute(), 0, 60), 0, 24, 0, TWO_PI * 2) - HALF_PI;
  
  // Draw the hands of the clock
  stroke(255);
  strokeWeight(1);
  line(cx, cy, cx + cos(s) * secondsRadius, cy + sin(s) * secondsRadius);
  strokeWeight(2);
  line(cx, cy, cx + cos(m) * minutesRadius, cy + sin(m) * minutesRadius);
  strokeWeight(4);
  line(cx, cy, cx + cos(h) * hoursRadius, cy + sin(h) * hoursRadius);
  
  // Draw the minute ticks
  strokeWeight(2);
  beginShape(POINTS);
  for (int a = 0; a < 360; a+=6) {
    float angle = radians(a);
    float x = cx + cos(angle) * secondsRadius;
    float y = cy + sin(angle) * secondsRadius;
    vertex(x, y);
  }
  endShape();
}

void draw() {
 /* int riconosci = 0;
  int flag =0;*/

  if (cam.available()) {
    cam.read();
  }
  weather.update();
  // Create the Choreo object using your Temboo session



  scale(-1.0, 1.0); // mirror effect (we on't want a webcam!)
  //image(cam, -720, 0, 2260,1280);
  image(cam, -screenH, 0, screenH*factor, screenW*factor);///2260,1280);
  
  fill(0, 150);
  noStroke();
  

 // riconosci=riconosci();
  //if (riconosci > 0)
  //flag = 1;*/ 
  //{
    

    if (millis()>lastime + dtime) {
      lastime = millis();
      weather.update();
      s = ("\nCittà: "+weather.getCityName()
    +"\nRegione: "+weather.getRegionName()
    +"\nPaese: "+weather.getCountryName()
    +"\nAlba: "+weather.getSunrise()
    +"\nTemperatura: "+weather.getTemperature()+"°"
    +"\nUmidità: "+weather.getHumidity()+"%"
    );
      c= calendar();
      m = mail();
    }

rect(-screenW+60, 0, 210, screenH);
    fill(255);
    scale(-1.0, 1.0);
    text("           Meteo di oggi \n\n",695, 200, 200, 720);
    textSize(16);
    text(s, 695, 220, 200, 720);  // Text wraps within text box
    textSize(16);
    text(c,695, 430, 215, 720);
    textSize(16);
    text(m, 695, 650, 200, 720);
    textSize(16);
    clock();
  }
//}
//
//boolean sketchFullScreen(){
//
//return true;
//}
