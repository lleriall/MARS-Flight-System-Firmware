#include "page.h"

extern const char* responseXX =R"html(<!DOCTYPE html>
    <html>
      <head>
        <title>HIVE 2</title>
        <meta name="viewport" content="width=device-width, initial-scale=1">
        <link rel= "stylesheet" type= "text/css" href= "styles.css">
        <style>
          html { font-family: sans-serif; text-align: center; background-color: rgb(0, 0, 0);}
          body { display: inline-flex; flex-direction: column;overflow: hidden; }

          #unit-title{
            color: #fff;
            left: 2%;
            top: 2%;
          }
          #config-menu{
            position: absolute;
            width: 29.5%;
            height: 70%;
            border-radius: 5px;
            border-radius: 15px;
            box-shadow: 0px 5px 10px 0px rgba(0, 0, 0, 0.5);
            left: 0.5%;
            top: 0%;
            background-color: rgb(35, 35, 35);
          }
          #terminal-area{
            position: absolute;
            width: 29.5%;
            height: 28.5%;
            border-radius: 15px;
            box-shadow: 0px 5px 10px 0px rgba(0, 0, 0, 0.5);
            left: 0.5%;
            top: 70.5%;
            background-color: rgb(35, 35, 35);
          }
          #attitude-ind-area{
            position: absolute;
            width: 34%;
            height: 48%;
            border-radius: 15px;
            box-shadow: 0px 5px 10px 0px rgba(0, 0, 0, 0.5);
            left: 30.5%;
            top: 0%;
            background-color: rgb(35, 35, 35);
          }
          #map-ind-area{
            position: absolute;
            width: 34%;
            height: 48%;
            border-radius: 15px;
            box-shadow: 0px 5px 10px 0px rgba(0, 0, 0, 0.5);
            left:65%;
            top: 0%;
            background-color: rgb(35, 35, 35);
          }
          #altitude-graph{
            position: absolute;
            width: 25%;
            height: 25%;
            border-radius: 15px;
            box-shadow: 0px 5px 10px 0px rgba(0, 0, 0, 0.5);
            left:56%;
            top: 49%;
            background-color: rgb(35, 35, 35);
          }
          #velocity-graph{
            position: absolute;
            width: 25%;
            height: 25%;
            border-radius: 15px;
            box-shadow: 0px 5px 10px 0px rgba(0, 0, 0, 0.5);
            left:30.5%;
            top: 49%;
            background-color: rgb(35, 35, 35);
          }
          #throttle-graph{
            position: absolute;
            width: 25%;
            height: 24%;
            border-radius: 15px;
            box-shadow: 0px 5px 10px 0px rgba(0, 0, 0, 0.5);
            left:30.5%;
            top: 75%;
            background-color: rgb(35, 35, 35);
          }
          #R1-graph{
            position: absolute;
            width: 25%;
            height: 24%;
            border-radius: 15px;
            box-shadow: 0px 5px 10px 0px rgba(0, 0, 0, 0.5);
            left:56%;
            top: 75%;
            background-color: rgb(35, 35, 35);
          }
          #data-area{
            position: absolute;
            width: 18%;
            height: 50%;
            border-radius: 15px;
            box-shadow: 0px 5px 10px 0px rgba(0, 0, 0, 0.5);
            left:81.5%;
            top: 49%;
            background-color: rgb(35, 35, 35);
          }
          #HIVE-IMG{
            position: absolute;
            width: 80%;
            height:30%;
            left:10%;
            top:15%;
            background-color: rgb(0, 0, 0);
            border-radius: 15px;
            box-shadow: 0px 5px 10px 0px rgba(0, 0, 0, 0.5);
          }

          #HIVE-PIC{
            position: absolute;
            width: 110%;
            height:90%;
            left: 0%;
            top:0%;
            max-width:100%;
            max-height:100%;
            object-fit: contain;
            border-radius: 15px;
          }
          #DRONE-STATE{
            position: absolute;
            width: 40%;
            height:10%;
            left:30%;
            top:50%;
            border-radius: 30px;
            box-shadow: 0px 5px 15px 0px rgba(0, 0, 0, 0.5);
            color: rgb(0, 0, 0);
            text-align: center;
            font-weight: bolder;
            justify-content: center;
            align-items: center;
            display: flex;
            background-color: #fff;
          }
          #terminal-input{
            position: absolute;
            width: 90%;
            height:20%;
            left:5%;
            top:10%;
            background-color: rgb(0, 0, 0);
            border-radius: 15px;
            border-style: none;
            box-shadow: 0px 5px 15px 0px rgba(0, 0, 0, 0.5);
            color: rgb(255, 255, 255);
          }
          #terminal-panel{
            position: absolute;
            width: 90%;
            height:60%;
            left:5%;
            top:35%;
            background-color: rgb(0, 0, 0);
            border-radius: 15px;
            border-style: none;
            box-shadow: 0px 5px 15px 0px rgba(0, 0, 0, 0.5);
            color: rgb(255, 255, 255);

          }
          #Raw-Data{
            margin-top: 10%;
            margin-left: 20%;
            color: #fff;
            padding-bottom: 10%;
          }
          #Config{
            position: absolute;
            width: 80%;
            height:30%;
            left:10%;
            top:65%;
            background-color: rgb(35, 35, 35);
            border-radius: 15px;
            box-shadow: 0px 5px 10px 0px rgba(0, 0, 0, 0.5);
          }
          #config-title{
            color: #fff;
          }
        </style>

      </head>
            
      <body>
        
        <div id = "config-menu">
            <h1 id = "unit-title">HIVE 2 UNIT</h1>
            <div id = "HIVE-IMG">
            </div>
            <div id = "DRONE-STATE"> STANDBY</div>
            <div id = "Config"> 
              <h3 id = "config-title"> Configuration</h3>
            </div>
        </div>
        
        <div id = "attitude-ind-area">
          <canvas id="drawingCanvas"></canvas>
        </div>

        <div id = "map-ind-area">
          <div id="map" style="width: 100%; height: 100%; border-radius: 15px;"></div>
        </div>

        <div id = "terminal-area">
            
            <input type="text" id="terminal-input" placeholder="CMD">
          
            <input type="text" id="terminal-panel" placeholder="Quick Access Terminal">
        </div>

        <div id = "altitude-graph">
          <canvas id="altitudeChart" ></canvas>
        </div>
        
        <div id = "velocity-graph">
          <canvas id="velocityChart" ></canvas>
        </div>

        <div id = "throttle-graph">
          <canvas id="throttleChart" ></canvas>
        </div>

        <div id = "R1-graph">
          <canvas id="R1Chart" ></canvas>
        </div>

        <div id = "data-area">
          <table id = "Raw-Data">
            <thead>
              <tr>
                <th>Variable</th>
                <th>Value</th>
              </tr>
            </thead>
            <tbody>
              <tr>
                <td>Latitude</td>
                <td>0</td>
              </tr>
              <tr>
                <td>Longitude</td>
                <td>0</td>
              </tr>
              <tr>
                <td>Satellites</td>
                <td>0</td>
              </tr>
              <tr>
                <td>Pitch</td>
                <td>0</td>
              </tr>
              <tr>
                <td>Roll</td>
                <td>0</td>
              </tr>
              <tr>
                <td>Yaw</td>
                <td>0</td>
              </tr>
              <tr>
                <td>WingFL</td>
                <td>0</td>
              </tr>
              <tr>
                <td>WingFR</td>
                <td>0</td>
              </tr>
              <tr>
                <td>WingRL</td>
                <td>0</td>
              </tr>
              <tr>
                <td>WingRR</td>
                <td>0</td>
              </tr>
            </tbody>
          </table>
        </div>


        <script type="text/javascript">

          //ALTITUDE CHART
          document.addEventListener('DOMContentLoaded', function() {
              const xValues = [100, 200, 300, 400, 500, 600, 700, 800, 900, 1000];
              Chart.defaults.global.defaultFontColor = "#fff";
              new Chart("altitudeChart", {
                  type: "line",
                  data: {
                      labels: xValues,
                      datasets: [{
                          data: [860, 1140, 1060, 1060, 1070, 1110, 1330, 2210, 7830, 2478],
                          borderColor: "green",
                          backgroundColor: "rgba(128, 128, 128, 0.2)", // Grey background color
                          fill: true
                      }, {

                      }]
                  },
                  options: {
                    title: {
                      display: true,
                      text: "Altitude",
                      fontColor: "#fff",
                      fontSize: 16,
                    },
                      legend: { display: false }
                  }
              });
          });

          //VELOCITY CHART
          document.addEventListener('DOMContentLoaded', function() {
              const xValues = [100, 200, 300, 400, 500, 600, 700, 800, 900, 1000];
              Chart.defaults.global.defaultFontColor = "#fff";
              new Chart("velocityChart", {
                  type: "line",
                  data: {
                      labels: xValues,
                      datasets: [{
                          data: [860, 1140, 1060, 1060, 1070, 1110, 1330, 2210, 7830, 2478],
                          borderColor: "green",
                          backgroundColor: "rgba(128, 128, 128, 0.2)", // Grey background color
                          fill: true
                      }, {

                      }]
                  },
                  options: {
                    title: {
                      display: true,
                      text: "Velocity",
                      fontColor: "#fff",
                      fontSize: 16,
                    },
                      legend: { display: false }
                  }
              });
          });

          //THROTTLE CHART
          document.addEventListener('DOMContentLoaded', function() {
              const xValues = [100, 200, 300, 400, 500, 600, 700, 800, 900, 1000];
              Chart.defaults.global.defaultFontColor = "#fff";
              new Chart("throttleChart", {
                  type: "line",
                  data: {
                      labels: xValues,
                      datasets: [{
                          data: [860, 1140, 1060, 1060, 1070, 1110, 1330, 2210, 7830, 2478],
                          borderColor: "green",
                          backgroundColor: "rgba(128, 128, 128, 0.2)", // Grey background color
                          fill: true
                      }, {

                      }]
                  },
                  options: {
                    title: {
                      display: true,
                      text: "Throttle",
                      fontColor: "#fff",
                      fontSize: 16,
                    },
                      legend: { display: false }
                  }
              });
          });

          //R1 CHART
          document.addEventListener('DOMContentLoaded', function() {
              const xValues = [100, 200, 300, 400, 500, 600, 700, 800, 900, 1000];
              Chart.defaults.global.defaultFontColor = "#fff";
              new Chart("R1Chart", {
                  type: "line",
                  data: {
                      labels: xValues,
                      datasets: [{
                          data: [860, 1140, 1060, 1060, 1070, 1110, 1330, 2210, 7830, 2478],
                          borderColor: "green",
                          backgroundColor: "rgba(128, 128, 128, 0.2)", // Grey background color
                          fill: true
                      }, {

                      }]
                  },
                  options: {
                    title: {
                      display: true,
                      text: "R1",
                      fontColor: "#fff",
                      fontSize: 16,
                    },
                      legend: { display: false }
                  }
              });
          });

          function displayWaypointsAndTrace() {
            // Initialize the map
            var map = L.map("map").setView([51.505, -0.09], 13);

            // Add a tile layer with a dark map theme and colored text
            L.tileLayer('https://{s}.basemaps.cartocdn.com/rastertiles/dark_all/{z}/{x}/{y}.png', {
              attribution: 'Map data &copy; <a href="https://www.openstreetmap.org/">OpenStreetMap</a> contributors',
              maxZoom: 18
            }).addTo(map);

            // Define an array of waypoints (lat, long)
            var waypoints = [
              [51.505, -0.09],
              [51.51, -0.1],
              [51.5, -0.08],
            ];

            // Create an empty trace layer
            var trace = L.polyline([], { color: "red" }).addTo(map);

            // Iterate over the waypoints
            waypoints.forEach(function (waypoint) {
              // Create a marker for each waypoint
              L.marker(waypoint).addTo(map);

              // Add the waypoint to the trace
              trace.addLatLng(waypoint);
            });

            // Fit the map to the bounds of the trace
            map.fitBounds(trace.getBounds());
          }

          // Call the function to display the waypoints and trace
          displayWaypointsAndTrace();


      </script>
      </body>
    </html>)html";
