var state = {};

var width = 800, height = 600;

//SETTINGS - SVG
var svg = d3.select("#svg").append("svg").attr("width", width).attr("height", height);


//SETTINGS - CANVAS
var scene = new THREE.Scene();
var camera = new THREE.PerspectiveCamera(75, width / height, 0.1, 1000);
var renderer = new THREE.WebGLRenderer();
renderer.setSize(width, height);
document.body.querySelector("#canvas").appendChild(renderer.domElement);

camera.position.z = 1.8;
camera.position.y = -3;
camera.rotation.x = Math.PI / 3;

var light = new THREE.PointLight();

light.position.z = 2;
light.position.y = -3;
light.position.x = -1;
scene.add(light);


//ELEMENTS - CANVAS
var axis_canvas = AxisCanvas();

scene.add(axis_canvas);

renderer.render(scene, camera);

//ELEMENTS - SVG


//INTERACTIONS
function animate() {
    //Recursion
    requestAnimationFrame(animate);

    //CANVAS ELEMENTS
    axis_canvas.rotation.x += 0.01;
    axis_canvas.rotation.y += 0.01;
    axis_canvas.rotation.z += 0.01;

    axis_canvas.rotation.x = axis_canvas.rotation.x > 2 * Math.PI ? 0 : axis_canvas.rotation.x;
    axis_canvas.rotation.y = axis_canvas.rotation.y > 2 * Math.PI ? 0 : axis_canvas.rotation.y;
    axis_canvas.rotation.z = axis_canvas.rotation.z > 2 * Math.PI ? 0 : axis_canvas.rotation.z;

    renderer.render(scene, camera);

    //CABEÇALHO
    d3.select("#pitch").text(formatFloat("" + axis_canvas.rotation.y) + "\trad");
    d3.select("#roll").text(formatFloat("" + axis_canvas.rotation.x) + "\trad");
    d3.select("#yaw").text(formatFloat("" + axis_canvas.rotation.z) + "\trad");

    //SVG ELEMENTS
}

function draw(_state) {
    //SETTING STATE
    _state = _state || state;
    state = typeof _state == "string" ? JSON.parse(_state) : _state;
    state.time = new Date(state.time);

    //CABEÇALHO
    d3.select("#pitch").text(state.pitch);
    d3.select("#roll").text(state.roll);
    d3.select("#yaw").text(state.yaw);


    //CANVAS ELEMENTS
    axis_canvas.rotation.x = state.pitch;
    axis_canvas.rotation.y = state.roll;
    axis_canvas.rotation.z = state.yaw;

    renderer.render(scene, camera);

    //SVG ELEMENTS
}

//startCanvas(animate);

setInterval(getValue,10);