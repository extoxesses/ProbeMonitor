const char index_page[] PROGMEM = R"=====(
<!DOCTYPE html>
<html>
    <head>
        <link rel="stylesheet" href="https://fonts.googleapis.com/css?family=Montserrat">
        <link rel="stylesheet" href="https://cdn.jsdelivr.net/npm/bootstrap@4.3.1/dist/css/bootstrap.min.css" integrity="sha384-ggOyR0iXCbMQv3Xipma34MD+dH/1fQ784/j6cY/iJTQUOhcWr7x9JvoRxT2MZw1T" crossorigin="anonymous">
        <style>
            body {
                font-family: Montserrat;
                margin: 1% 10%;
                background-color: black;
                color: white;
            }
            .header {
                display: flex;
                flex-direction: row;
                justify-content: space-between;
                padding: 1%;
                margin-bottom: 5%;
                border-bottom: 1px solid white;
            }
            .header-title {
                font-size: 3em;
            }
            .date {
                align-self: self-end;
            }
            .flex-container {
                display: flex;
                justify-content: space-around;
            }
            .flex-column {
                flex-direction: column;
            }
            .flex-row {
                padding-left: 2%;
                justify-content: unset;
            }
            .flex-item {
                margin: 2.5%;
                padding-left: 1%;
                /* border-left: 5px solid green; */
                /* border-left: 5px solid; */
            }
            .flex-item-title {
                font-size: 2em;
            }
            .value-1 {
                padding-left: 1%;
            }
            .footer {
                display: flex;
                justify-content: end;
                margin: 5% 2%;
            }
            .activated {
                border-left: 5px solid green;
            }
            .deactivated {
                border-left: 5px solid red;
            }
        </style>
    </head>
    <body>        
        <div>
            <div class="header">
                <div class="header-title">
                    Boiler probe monitor
                </div>
                <div id="date" class="date"></div>
            </div>
        </div>
        <div>
            <div class="flex-container flex-column" id="probes"></div>
        </div>
        <div>
            <div class="footer">
                <div class="value-1">
                    <button type="button" class="btn btn-light" onclick="download()">Download</button>
                </div>
                <div class="value-1">
                    <button type="button" class="btn btn-info" onclick="getWheather()">Wheather</button>
                </div>
            </div>
        </div>
        
        <script>
            function download() {
                window.open(`${window.location.href}download`, 'test.csv');
            }

            function getSnapshot() {
                fetch(`${window.location.href}read`)
                    .then(response => {
                        if (!response.ok) {
                            throw new Error(`Invalid server response: ${response.status}`)
                        }
                        return response.text();
                    })
                    .then(body => {
                        const place = document.getElementById('probes');
                        place.innerHTML = "";
                        body.split('\n')
                            .forEach(row => place.insertAdjacentHTML('beforeend', parseProbeData(row)))
                    })
                    .catch(error => { 
                        console.log(error)
                    })
            }

            function getWheather() {
                window.location.href = 'https://wttr.in'
            }
            
            function parseProbeData(row) {
                const data = row.split(';');
                const isActive = data[1] > 1;
                const activeStyle = isActive ? 'activated' : 'deactivated';

                return `<div class="flex-item ${activeStyle}">
                    <div>
                        <div class="flex-item-title">Probe n.${data[0]}</div>
                    </div>
                    <div class="flex-container flex-column">
                        <div>
                            <div class="flex-container flex-row">
                                <div class="value-1">Status:</div>
                                <div class="value-1">${isActive}</div>
                            </div>
                            <div class="flex-container flex-row">
                                <div class="value-1">Temperature (degrees): </div>
                                <div class="value-1">${data[2]}</div>
                            </div>
                        </div>
                    </div>
                </div>`
            }

            function setTime() {
                const now = new Date();
                const date = `${now.getHours()}:${now.getMinutes()} - ${now.getDate()}/${now.getMonth() + 1}/${now.getFullYear()}`;
                document.getElementById("date").innerHTML = date;
            }

            window.onload = function() {
                setTime();
                getSnapshot();
            }

            setInterval(setTime, 10000);
            setInterval(getSnapshot, 60000);
        </script>
    </body>
</html>
)=====";