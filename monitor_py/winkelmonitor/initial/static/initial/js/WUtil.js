function formatFloat(f, ncasas) {
    ncasas = ncasas || 2;
    var pow = Math.pow(10, ncasas);
    return Math.round(f * pow) / pow;
}

function http_get(url, funct,recall) {
    var xhr = new XMLHttpRequest();
    xhr.open('GET', url);
    xhr.onload = function () {
        if (xhr.status === 200) {
            funct(xhr.responseText);
            if(recall)
                http_get(url,funct,recall)
        }
        else {
            //alert('Request failed.  Returned status of ' + xhr.status);
        }
    };
    xhr.send();
}

function startCanvas() {
    if (WEBGL.isWebGLAvailable()) {

        // Initiate function or other initializations here
        animate();
    } else {

        var warning = WEBGL.getWebGLErrorMessage();
        document.getElementById('container').appendChild(warning);

    }
}

function startHttp(){
    getValue(true);
}