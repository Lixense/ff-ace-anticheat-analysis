// frida_brute_iv.js — in the app JVM, download the lib and brute AES-CTR IV candidates.
'use strict';
function hex2(b) {
    if (!b) return '';
    var r = '';
    for (var i = 0; i < b.length; i++) r += ('0' + (b[i] & 0xff).toString(16)).slice(-2);
    return r;
}
function jarr(js) {
    return Java.array('byte', js);
}
Java.perform(function () {
    try {
        var URL = Java.use('java.net.URL');
        var ByteArrayOutputStream = Java.use('java.io.ByteArrayOutputStream');
        var Cipher = Java.use('javax.crypto.Cipher');
        var SecretKeySpec = Java.use('javax.crypto.spec.SecretKeySpec');
        var IvParameterSpec = Java.use('javax.crypto.spec.IvParameterSpec');
        var String = Java.use('java.lang.String');

        var url = 'https://sx2lador.online/DevZerzXpProxy/L/libXZAXZAXZAXZA.so';
        var keyStr = 'f7a2c9d1e8b34560ac7ef1230d9b56e4';

        var u = URL.$new(url);
        var conn = u.openConnection();
        conn.setConnectTimeout(20000);
        conn.setReadTimeout(30000);
        var is = conn.getInputStream();
        var bos = ByteArrayOutputStream.$new();
        var buf = jarr(new Array(8192).fill(0));
        var n;
        while ((n = is.read(buf)) > 0) {
            bos.write(buf, 0, n);
        }
        is.close();
        var blob = bos.toByteArray();
        console.log('[brute] downloaded ' + blob.length + ' bytes');
        console.log('[brute] head ' + hex2(jarr(Array.prototype.slice.call(blob, 0, 16))));

        var keyBytes = String.$new(keyStr).getBytes('UTF-8');
        var keyArr = Array.prototype.slice.call(keyBytes);

        var ivs = {};
        ivs['zero16'] = new Array(16).fill(0);
        var x4 = []; for (var i = 0; i < 4; i++) x4 = x4.concat([120, 52, 82, 113]);
        ivs['x4Rq_x4'] = x4;
        var k16 = []; for (var i = 0; i < keyArr.length; i += 2) k16.push(parseInt(keyStr.substr(i, 2), 16));
        ivs['hexkey16'] = k16;
        ivs['ascii16a'] = keyArr.slice(0, 16);
        ivs['ascii16b'] = keyArr.slice(16, 32);
        var MessageDigest = Java.use('java.security.MessageDigest');
        var md = MessageDigest.getInstance('MD5'); md.update(keyBytes);
        ivs['md5'] = Array.prototype.slice.call(md.digest());
        var sh = MessageDigest.getInstance('SHA-1'); sh.update(keyBytes);
        ivs['sha1'] = Array.prototype.slice.call(sh.digest()).slice(0, 16);
        // also the 4-byte 'x4Rq' raw + zero pad variants
        var x4z = [120, 52, 82, 113].concat(new Array(12).fill(0));
        ivs['x4Rq_pad0'] = x4z;
        var x4o = [120, 52, 82, 113].concat(new Array(12).fill(1));
        ivs['x4Rq_pad1'] = x4o;

        Object.keys(ivs).forEach(function (nm) {
            try {
                var c = Cipher.getInstance('AES/CTR/NoPadding');
                c.init(2, SecretKeySpec.$new(jarr(keyArr), 'AES'), IvParameterSpec.$new(jarr(ivs[nm])));
                var pt = c.doFinal(blob);
                var headArr = Array.prototype.slice.call(pt, 0, 4);
                var head = hex2(headArr);
                var isElf = head === '7f454c46';
                console.log('[brute] ' + nm + ' ok head=' + head + (isElf ? ' *** ELF ***' : ''));
                if (isElf) {
                    var FileOutputStream = Java.use('java.io.FileOutputStream');
                    var fos = FileOutputStream.$new('/data/local/tmp/decrypted.so');
                    fos.write(pt);
                    fos.close();
                    console.log('[brute] SAVED /data/local/tmp/decrypted.so');
                }
            } catch (e) {
                console.log('[brute] ' + nm + ' FAIL ' + e);
            }
        });
        console.log('[brute] done');
    } catch (e) {
        console.log('[brute] top err ' + e);
    }
});
