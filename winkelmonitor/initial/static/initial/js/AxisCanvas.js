function setCenter(geometry, x, y, z) {
    geometry.applyMatrix(new THREE.Matrix4().makeTranslation(x, y, z));
}

var Material = THREE.MeshLambertMaterial;

function AxisCanvas() {
    var axis_canvas = new THREE.Group();
    //Origin - Axis
    var geometry = new THREE.SphereGeometry( 0.2, 32, 32 );
    var material = new Material({ color: 0xFFFF00, side: THREE.DoubleSide });
    var origin = new THREE.Mesh(geometry, material);
    axis_canvas.add(origin);

    //Y - Axis
    var geometry = new THREE.CylinderGeometry(0.05, 0.05, 2, 30);
    setCenter(geometry, 0, 1, 0);
    var material = new Material({ color: 0x00ff00, side: THREE.DoubleSide });
    var yaxis = new THREE.Mesh(geometry, material);
    axis_canvas.add(yaxis);

    var geometry = new THREE.CylinderGeometry(0.0, 0.1, 0.2, 30);
    var material = new Material({ color: 0x00ff00, side: THREE.DoubleSide });
    var yarrow = new THREE.Mesh(geometry, material);
    yarrow.position.y = 2;
    axis_canvas.add(yarrow);

    //X - Axis
    var geometry = new THREE.CylinderGeometry(0.05, 0.05, 2, 30);
    setCenter(geometry, 0, 1, 0);
    var material = new Material({ color: 0xff0000, side: THREE.DoubleSide });
    var xaxis = new THREE.Mesh(geometry, material);
    xaxis.rotation.z = -Math.PI / 2;
    axis_canvas.add(xaxis);

    var geometry = new THREE.CylinderGeometry(0.0, 0.1, 0.2, 30);
    var material = new Material({ color: 0xff0000, side: THREE.DoubleSide });
    var xarrow = new THREE.Mesh(geometry, material);
    xarrow.position.x = 2;
    xarrow.rotation.z = -Math.PI / 2;
    axis_canvas.add(xarrow);

    //Z - Axis
    var geometry = new THREE.CylinderGeometry(0.05, 0.05, 2, 30);
    setCenter(geometry, 0, 1, 0);
    var material = new Material({ color: 0x0000ff, side: THREE.DoubleSide });
    var zaxis = new THREE.Mesh(geometry, material);
    zaxis.rotation.x = Math.PI / 2;
    axis_canvas.add(zaxis);

    var geometry = new THREE.CylinderGeometry(0, 0.1, 0.2, 30);
    var material = new Material({ color: 0x0000ff, side: THREE.DoubleSide });
    var zarrow = new THREE.Mesh(geometry, material);
    zarrow.position.z = 2;
    zarrow.rotation.x = Math.PI / 2;
    axis_canvas.add(zarrow);

    return axis_canvas;
}