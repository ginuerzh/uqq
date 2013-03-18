import QtQuick 2.0
import Ubuntu.Components 0.1
import UQQ 1.0
import "md5.js" as MD5

Item {
    id: loginForm
    width: units.gu(45)
    height: units.gu(80)

    Column {
        anchors.centerIn: parent
        spacing: units.gu(1)

        Image {
            source: "logo.png"
        }

        Label {
            id: errMsg
            width: parent.width
            clip: true

            color: "red"
            text: " "
        }

        FormInput {
            id: username

            label: i18n.tr("用户名:")
            placeholderText: i18n.tr("QQ号码")
            KeyNavigation.tab: password
            focus: true
            onFocusChanged: {
                if (!focus && text.length > 0 && text != loginData.uin) {
                    loginData.uin = text;
                    checkVC(loginData);
                }
            }
            //validator: RegExpValidator { regExp: /\d{5,}/ }
        }
        FormInput {
            id: password

            label: i18n.tr("密    码:")
            echoMode: TextInput.Password
            KeyNavigation.tab: captcha.visible ? captcha : username
            KeyNavigation.backtab: username
        }
        FormInput {
            id: captcha

            label: i18n.tr("验证码:")
            visible: false

            KeyNavigation.tab: username
            KeyNavigation.backtab: password
        }

        Rectangle {
            width: parent.width
            height: childrenRect.height

            Image {
                id: captchaImg
                anchors.left: parent.left
                height: loginButton.height
                visible: false
            }
            Button {
                id: loginButton
                anchors.right: parent.right
                text: i18n.tr("登录")

                onClicked: {
                    loginData.password = password.text;
                    if (captcha.visible)
                        loginData.vc = captcha.text;

                    login(loginData);
                }
            }
        }
    }

    QtObject {
        id: loginData

        property string uin
        property string password
        property string vc
        property string uinBytes
        property string appid: "1003903"
        readonly property var status: ({
            online: "online",   // 在线
            callme: "callme",   // Q我吧
            away:   "away",     // 离开
            busy:   "busy",     // 忙碌
            slient: "silent",   // 请勿打扰
            hidden: "hidden",   // 隐身
            offline:"offine"    // 离线
        })

        property string vfwebqq
        property string psessionid

        onVfwebqqChanged: getFirends(vfwebqq);
    }

    HttpClient {
        id: loginClient
    }

    JSONListModel {
        id: loginModel
        query: "$"
        onJsonChanged: {
            if (count > 0) {
                var retcode = model.get(0).retcode;
                if (retcode !== 0) {
                    console.debug("login failed, retcode=" + retcode);
                } else {
                    var result = model.get(0).result;
                    loginData.vfwebqq = result.vfwebqq;
                    loginData.psessionid = result.psessionid;
                    console.log("vfwebqq:" + loginData.vfwebqq);
                    console.log("psessionid:" + loginData.psessionid);
                }
            } else {
                console.log("no data");
            }
        }
    }

    // check whether captcha is needed
    function checkVC(data) {
        var url = "http://check.ptlogin2.qq.com/check?" +
                "uin=" + data.uin +
                "&appid=" + data.appid +
                "&r=" + Math.random();

        loginClient.open(HttpClient.Get, url);
        loginClient.setHeader("Referer", "http://d.web2.qq.com/proxy.html?v=20110331002&callback=1&id=3");
        loginClient.send();
        loginClient.textFinished.connect(onLoginCheck);
    }

    function geCaptcha(data) {
        var url = "http://captcha.qq.com/getimage?" +
                "uin=" + data.uin +
                "&vc_type=" + data.vc +
                "&aid=" + data.appid +
                "&r=" + Math.random();

        captchaImg.source = url;
    }

    function login(data) {
        var url = "http://ptlogin2.qq.com/login?" +
                "u=" + data.uin +
                "&p=" + pwdMd5(data) +
                "&verifycode=" + data.vc +
                "&aid=" + data.appid +
                "&webqq_type=10&remember_uin=0&login2qq=1&u1=http%3A%2F%2Fweb.qq.com%2Floginproxy.html%3Flogin2qq%3D1%26webqq_type%3D10&h=1&ptredirect=0&ptlang=2052&from_ui=1&pttype=1&dumy=&fp=loginerroralert&action=2-6-22950&mibao_css=m_webqq&t=1&g=1"

        loginClient.open(HttpClient.Get, url);
        loginClient.setHeader("Referer", "http://d.web2.qq.com/proxy.html?v=20110331002&callback=1&id=3");
        loginClient.textFinished.connect(onLoginCheck);
        loginClient.send();
    }
    function onLoginCheck(text) {
        loginClient.textFinished.disconnect(onLoginCheck);
        eval(text);
    }

    // 1279450562
    function secondLogin() {
        var url = "http://d.web2.qq.com/channel/login2";

        var data = "r={" +
                "\"status\":\"" + loginData.status.hidden + "\"" +
                ",\"ptwebqq\":\"" + loginClient.getCookie("ptwebqq", url) + "\"" +
                ",\"passwd_sig\":\"\"" +
                ",\"clientid\":\"25499193\"" +
                ",\"psessionid\":null}&clientid=25499193&psessionid=null";

        loginClient.open(HttpClient.Post, url);
        loginClient.setHeader("Content-Type", "application/x-www-form-urlencoded");
        loginClient.setHeader("Referer", "http://d.web2.qq.com/proxy.html?v=20110331002&callback=1&id=3");
        loginClient.textFinished.connect(onSecondLogin);
        loginClient.send(loginClient.toPercentEncoding(data, "=", null));
    }
    function onSecondLogin(text) {
        //console.log(text)
        loginClient.textFinished.disconnect(onSecondLogin);
        loginModel.json = text;
    }

    function getFirends(vfwebqq) {
        var url = "http://s.web2.qq.com/api/get_user_friends2";
        var data = "r={\"h\":\"hello\"" +
                    ",\"vfwebqq\":\"" + vfwebqq + "\"}"

        loginClient.open(HttpClient.Post, url);
        loginClient.setHeader("Content-Type", "application/x-www-form-urlencoded");
        loginClient.setHeader("Referer", "http://d.web2.qq.com/proxy.html?v=20110331002&callback=2");
        loginClient.textFinished.connect(onGetFirends);
        loginClient.send(loginClient.toPercentEncoding(data, "=", null));
    }
    function onGetFirends(text) {
        console.log(text);
    }

    function pwdMd5(data) {
        // though QML has the Qt.md5 function,
        // but the result it calculated doesn't match this.
        // so we need ourself md5 algorithm
        // thanks 'http://www.qicq5.com/' forum for this algorithm.

        var I = MD5.hexchar2bin(MD5.md5(data.password));
        var H = MD5.md5(I + data.uinBytes);
        var G = MD5.md5(H + data.vc.toUpperCase());
        //console.log(G);
        return G;
    }

    function ptui_checkVC(status, vc, uin) {
        //console.log("ptui_checkVC(" + status + ", " + vc + ", " + uin + ")");

        loginData.vc = vc;
        loginData.uinBytes = uin;
        if (parseInt(status) !== 0 && vc.length > 0) {
            captchaImg.visible = true;
            captcha.visible = true;
            geCaptcha(loginData);
        } else {
            captchaImg.visible = false;
            captcha.visible = false;
        }
    }

    function ptuiCB(status,code, url, code2, text, name) {
        //console.log("ptuiCB(" + status + ", " + code + ", " +
        //            url + ", " + code2 + ", " + text + ", " + name + ")");
        if (parseInt(status) === 0) {
            errMsg.text = " ";
            secondLogin();
        } else {
            errMsg.text = text;
        }
    }
}
