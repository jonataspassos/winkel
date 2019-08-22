var state = {};

var width = 800, height = 600;

var svg = d3.select("#svg").append("svg").attr("width", width).attr("height", height);
var scene = new THREE.Scene();
var camera = new THREE.PerspectiveCamera(75, width / height, 0.1, 1000);
var renderer = new THREE.WebGLRenderer();
renderer.setSize(width, height);
document.body.querySelector("#canvas").appendChild(renderer.domElement);

camera.position.z = 2;
camera.position.y = -3;
camera.rotation.x = Math.PI / 3;

var light = new THREE.PointLight();

light.position.z = 2;
light.position.y = -3;
light.position.x = -1;
scene.add(light);

var axis_canvas = AxisCanvas();

scene.add(axis_canvas);

renderer.render(scene, camera);

function draw(_state) {
    _state = _state || state;
    state = typeof _state == "string" ? JSON.parse(_state) : _state;
    state.time = new Date(state.time);
    //            console.log(state);

    d3.select("#pitch").text(state.pitch);
    d3.select("#roll").text(state.roll);
    d3.select("#yaw").text(state.yaw);
}

function http_get(url, funct) {
    var xhr = new XMLHttpRequest();
    xhr.open('GET', url);
    xhr.onload = function () {
        if (xhr.status === 200) {
            funct(xhr.responseText);
        }
        else {
            alert('Request failed.  Returned status of ' + xhr.status);
        }
    };
    xhr.send();
}

function getValue() {
    http_get("{% url 'initial:getvalue' %}", draw)
}

        //setInterval(getValue,10);