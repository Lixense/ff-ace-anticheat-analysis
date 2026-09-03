// frida_capture_crypto.js — spawn-and-hook; also auto-triggers the main activity
'use strict';
function hex(b) {
    if (!b) return 'null';
    var r = '';
    for (var i = 0; i < b.length; i++) r += ('0' + (b[i] & 0xff).toString(16)).slice(-2);
    return r;
}
Java.perform(function () {
    var Cipher = Java.use('javax.crypto.Cipher');
    var Mac = Java.use('javax.crypto.Mac');
    var SecretKeySpec = Java.use('javax.crypto.spec.SecretKeySpec');
    var IvParameterSpec = Java.use('javax.crypto.spec.IvParameterSpec');

    Cipher.init.overloads.forEach(function (ov) {
        ov.implementation = function () {
            try {
                var alg = this.getAlgorithm();
                var info = 'Cipher.init ' + alg;
                for (var i = 0; i < arguments.length; i++) {
                    var a = arguments[i];
                    try {
                        if (a === null) info += ' arg' + i + '=null';
                        else if (a.getEncoded) info += ' key=' + hex(a.getEncoded());
                        else if (a.getIV) info += ' iv=' + hex(a.getIV());
                        else if (typeof a === 'number') info += ' opmode=' + a;
                    } catch (e) {}
                }
                console.log('[crypto] ' + info);
            } catch (e) { console.log('[crypto] init err ' + e); }
            return ov.apply(this, arguments);
        };
    });
    Mac.init.overloads.forEach(function (ov) {
        ov.implementation = function () {
            try {
                var a = arguments[0];
                var info = 'Mac.init ' + this.getAlgorithm();
                if (a && a.getEncoded) info += ' key=' + hex(a.getEncoded());
                console.log('[crypto] ' + info);
            } catch (e) {}
            return ov.apply(this, arguments);
        };
    });
    SecretKeySpec.$init.overloads.forEach(function (ov) {
        ov.implementation = function () {
            try { console.log('[crypto] new SecretKeySpec key=' + hex(arguments[0]) + ' alg=' + arguments[1]); }
            catch (e) {}
            return ov.apply(this, arguments);
        };
    });
    console.log('[crypto] hooks installed, launching main...');
    try {
        var Intent = Java.use('android.content.Intent');
        var context = Java.use('android.app.ActivityThread').currentApplication().getApplicationContext();
        var pm = context.getPackageManager();
        var launch = pm.getLaunchIntentForPackage('com.Sx2.Team.Ban');
        if (launch) {
            launch.addFlags(0x10000000);
            context.startActivity(launch);
            console.log('[crypto] launch intent sent');
        }
    } catch (e) { console.log('[crypto] launch err ' + e); }
});
