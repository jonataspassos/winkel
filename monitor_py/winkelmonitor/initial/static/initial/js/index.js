var state = {};

var width = 800, height = 600;

//SETTINGS - SVG
var svg = d3.select("#svg").select("svg").attr("width", width).attr("height", height);


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
var air_roll = svg.select("#orto-roll");
var air_pitch = svg.select("#orto-pitch");
var air_yaw = svg.select("#orto-yaw");
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
    air_roll.attr("transform","translate(75,75)rotate("+axis_canvas.rotation.x*180/Math.PI+")");
    air_pitch.attr("transform","translate(75,225)rotate("+axis_canvas.rotation.y*180/Math.PI+")");
    air_yaw.attr("transform","translate(75,375)rotate("+axis_canvas.rotation.z*180/Math.PI+")");
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
    air_roll.attr("transform","translate(75,75)rotate("+state.roll*180/Math.PI+")");
    air_pitch.attr("transform","translate(75,225)rotate("+state.pitch*180/Math.PI+")");
    air_yaw.attr("transform","translate(75,375)rotate("+state.yaw*180/Math.PI+")");

}
//startCanvas();

startHttp();

/**
 * step = [
        (state.pitch - axis_canvas.rotation.x) / 9,
        (state.roll - axis_canvas.rotation.y) / 9,
        (state.yaw - axis_canvas.rotation.z) / 9
    ]

    for (var i = 1; i <= 9; i++) {
        setTimeout(function () {
            //CANVAS ELEMENTS
            axis_canvas.rotation.x += step[0];
            axis_canvas.rotation.y += step[1];
            axis_canvas.rotation.z += step[2];

            //CABEÇALHO
            d3.select("#pitch").text(axis_canvas.rotation.y);
            d3.select("#roll").text(axis_canvas.rotation.x);
            d3.select("#yaw").text(axis_canvas.rotation.z);

            renderer.render(scene, camera);

            //SVG ELEMENTS
            air_roll.attr("transform", "translate(75,75)rotate(" + axis_canvas.rotation.x * 180 / Math.PI + ")");
            air_pitch.attr("transform", "translate(75,225)rotate(" + axis_canvas.rotation.y * 180 / Math.PI + ")");
            air_yaw.attr("transform", "translate(75,375)rotate(" + axis_canvas.rotation.z * 180 / Math.PI + ")");
        }, i);
    }
 */