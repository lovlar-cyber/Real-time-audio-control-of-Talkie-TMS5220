var eh = [24, 20, 6, 3, 5, 9, 9, 6, 2, 5];
var aeh1 = [26, 15, 9, 5, 3, 11, 7, 5, 5, 4];
var aeh2 = [25, 13, 11, 2, 5, 11, 7, 5, 3, 2];
var aeh3 = [26, 11, 10, 3, 7, 11, 7, 5, 3, 3];
var aeh4 = [24, 15, 9, 2, 9, 10, 7, 5, 3, 3];
var aeh5 = [23, 16, 6, 3, 10, 10, 9, 5, 3, 4];
var KKsold = [eh, aeh1, aeh2, aeh3, aeh4, aeh5];


var KKs = [[16, 20, 7, 6, 6, 9, 2, 6, 6, 5], [17, 24, 10, 6, 4, 13, 7, 6, 3, 3], [17, 23, 10, 7, 5, 10, 6, 6, 2, 4], [19, 15, 5, 6, 8, 9, 8, 7, 1, 3], [19, 15, 5, 6, 7, 9, 7, 7, 1, 3], [20, 17, 2, 6, 9, 8, 9, 5, 4, 2], [19, 19, 3, 5, 7, 8, 5, 6, 6, 2], [19, 19, 3, 5, 8, 9, 5, 6, 5, 2], [17, 20, 3, 6, 9, 7, 6, 6, 6, 1], [17, 19, 3, 6, 8, 9, 5, 6, 6, 3], [16, 14, 8, 6, 8, 9, 4, 3, 4, 2], [19, 23, 7, 7, 5, 9, 6, 5, 0, 5], [19, 27, 7, 9, 4, 11, 10, 5, 1, 5], [19, 19, 7, 5, 7, 13, 8, 6, 3, 3], [19, 19, 7, 5, 7, 13, 8, 6, 2, 3], [19, 19, 7, 5, 7, 13, 8, 6, 2, 3], [17, 18, 8, 8, 4, 7, 10, 6, 1, 5], [17, 17, 8, 8, 4, 6, 10, 6, 2, 3], [19, 18, 8, 7, 4, 6, 11, 6, 2, 3], [19, 18, 8, 7, 4, 6, 11, 6, 2, 3], [19, 19, 8, 7, 4, 5, 12, 7, 3, 3], [20, 13, 10, 4, 4, 3, 6, 5, 4, 4], [24, 9, 5, 4, 6, 6, 4, 4, 5, 5], [15, 8, 3, 10, 12, 4, 8, 6, 2, 5], [21, 9, 1, 6, 13, 11, 5, 5, 2, 4], [21, 10, 1, 5, 12, 10, 7, 6, 3, 5], [21, 10, 2, 4, 10, 9, 8, 6, 3, 4], [23, 13, 6, 2, 5, 7, 9, 6, 1, 5], [24, 9, 5, 2, 4, 10, 8, 4, 3, 5], [24, 9, 5, 2, 5, 10, 8, 4, 3, 5], [24, 9, 6, 2, 4, 9, 8, 3, 3, 5], [24, 9, 5, 2, 4, 10, 8, 4, 3, 5], [24, 9, 5, 1, 3, 10, 11, 6, 4, 4], [21, 10, 5, 3, 4, 8, 5, 6, 5, 5], [22, 13, 3, 5, 6, 8, 9, 6, 3, 3], [21, 12, 3, 6, 8, 9, 10, 6, 3, 3], [21, 12, 3, 5, 7, 9, 10, 7, 4, 4], [21, 12, 3, 5, 7, 9, 10, 6, 4, 4], [21, 7, 6, 5, 5, 5, 7, 5, 4, 4], [24, 12, 8, 3, 3, 4, 5, 7, 4, 3], [21, 9, 5, 5, 10, 6, 12, 7, 1, 3], [21, 9, 6, 5, 10, 6, 12, 6, 1, 3], [21, 9, 5, 5, 10, 6, 12, 6, 1, 3], [19, 9, 3, 7, 11, 5, 11, 5, 1, 4], [19, 8, 1, 6, 13, 6, 8, 5, 3, 6], [19, 8, 1, 6, 13, 6, 7, 5, 3, 6], [18, 8, 1, 7, 14, 6, 7, 6, 3, 5], [19, 9, 1, 7, 13, 5, 8, 5, 3, 4], [30, 13, 7, 5, 4, 6, 4, 3, 3, 4], [30, 15, 7, 8, 6, 8, 7, 3, 3, 4], [19, 11, 7, 6, 8, 4, 8, 6, 3, 3], [19, 13, 6, 9, 5, 8, 13, 5, 1, 3], [19, 13, 6, 9, 5, 8, 13, 5, 1, 4], [19, 13, 7, 9, 5, 7, 12, 5, 2, 4], [19, 13, 6, 9, 5, 8, 13, 5, 2, 4], [11, 17, 12, 10, 6, 7, 5, 2, 2, 3], [13, 12, 13, 10, 8, 7, 4, 2, 3, 4], [24, 12, 5, 6, 2, 12, 8, 4, 6, 4], [20, 13, 4, 6, 6, 9, 6, 6, 4, 3], [19, 19, 4, 4, 8, 11, 5, 5, 6, 3], [19, 20, 4, 4, 8, 11, 5, 6, 6, 3]];

var en = 14;
var re = 0;
var PIsold = [2, 4, 6, 8, 10, 28, 30, 32];
var PIs = linspaceVect(1, 38, 1);


var str = matrix(en, re, PIs, KKs);

console.log(str);



function matrix(en, re, PIs, KKs) {
    var rows = KKs.length;
    var cols = PIs.length;
    var pitch = 64 - cols;
    var temp;
    var res = "\nextern const uint8_t ehmat[" + rows + "][" + cols + "][7] PROGMEM={";
    for (var r = 0; r < rows; r++) {
        res = res.concat("\n{ ");
        for (var c = 0; c < cols; c++) {

            res = res.concat(to7bytes(en, re, pitch / 2 + PIs[c], KKs[r]));
            if ((c + 1) != cols) {
                res = res.concat(", ")
            }
        }
        res = res.concat(" }");
        if ((r + 1) != rows) {
            res = res.concat(",")
        }
    }
    res = res.concat("\n};\n");

    return res;
}

function linspaceVect(start, nvalues, interval) {
    if (typeof interval === "undefined") { interval = 0; }
    var i;
    var r = [];
    for (i = 0; i < nvalues; i++) {
        r.push(start + (i * interval));
    }
    return r;
}

function to7bytes(en, re, pi, Ks) {
    var res = "0000".substr(en.toString(2).length) + en.toString(2);
    var res = res.concat(re.toString(2));
    var res = res.concat("000000".substr(pi.toString(2).length) + pi.toString(2));
    var res = res.concat("00000".substr(Ks[0].toString(2).length) + Ks[0].toString(2));
    var res = res.concat("00000".substr(Ks[1].toString(2).length) + Ks[1].toString(2));
    var res = res.concat("0000".substr(Ks[2].toString(2).length) + Ks[2].toString(2));
    var res = res.concat("0000".substr(Ks[3].toString(2).length) + Ks[3].toString(2));
    var res = res.concat("0000".substr(Ks[4].toString(2).length) + Ks[4].toString(2));
    var res = res.concat("0000".substr(Ks[5].toString(2).length) + Ks[5].toString(2));
    var res = res.concat("0000".substr(Ks[6].toString(2).length) + Ks[6].toString(2));
    var res = res.concat("000".substr(Ks[7].toString(2).length) + Ks[7].toString(2));
    var res = res.concat("000".substr(Ks[8].toString(2).length) + Ks[8].toString(2));
    var res = res.concat("000".substr(Ks[9].toString(2).length) + Ks[9].toString(2));
    var res = res.concat("111100");
    return bin2hexstr(rev(res));
}

function rev(a) {
    var rest = a;
    res = "";
    for (var n = 0; n < a.length; n = n + 8) {
        var eight = parseInt(rest.substring(0, 8), 2);
        var reveight = rev8(eight).toString(2);
        revres = "00000000".substr(reveight.length) + reveight;
        res = res.concat(revres);
        rest = rest.substring(8);
    }
    return res;
}

function rev8(a) {
    // 76543210
    a = (a >> 4) | (a << 4); // Swap in groups of 4
    // 32107654
    a = ((a & 0xcc) >> 2) | ((a & 0x33) << 2); // Swap in groups of 2
    // 10325476
    a = ((a & 0xaa) >> 1) | ((a & 0x55) << 1); // Swap bit pairs
    // 01234567
    return a;
}
//"00000000".substr(reveight.length) + reveight;

function bin2hexstr(bin) {
    var binstr = "{";
    for (var i = 0; i < (bin.length / 8); i++) {
        var b8 = bin.substring(i * 8, i * 8 + 8);
        var hexbyte = parseInt(b8, 2).toString(16);
        binstr = binstr.concat("0x" + hexbyte + ",");
    }
    binstr = binstr.substring(0, binstr.length - 1);
    binstr = binstr.concat("}")
    return binstr;
}