.pragma library

WorkerScript.onMessage = function(msg) {
    var obj = null;
    var find = 0;

    for (var i = 0; i < msg.model.length; i++) {
        obj = msg.model[i];
        console.log(msg.uin + "/" + obj.uin);
        if (msg.uin == obj.uin) {
            find = 1;
            break;
        }
    }
    if (!find) return;
    console.log("sort.js: " + obj.uin + ", " + obj.status);
    find = 0;
    for (var i = 0; i < msg.model.length; i++) {
        var o = msg.model[i];
        if (obj.status <= o.status) {
            msg.model.insert(i, obj);
            find = 1;
            break;
        }
    }
    if (!find) msg.model.append(obj);
    msg.model.sync();
}
