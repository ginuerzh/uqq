import QtQuick 2.0
import Ubuntu.Components 0.1
import UQQ 1.0 as QQ
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
            text: QQ.Client.errCode ? QQ.Client.getInfo("errMsg") : " "
        }

        FormInput {
            id: username

            label: i18n.tr("用户名:")
            placeholderText: i18n.tr("QQ号码")
            KeyNavigation.tab: password
            focus: true
            onFocusChanged: {
                if (!focus && text.length > 0) {
                    QQ.Client.checkCode(text);
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
            visible: QQ.Client.captcha ? true : false

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
                visible: QQ.Client.captcha ? true : false
                source: QQ.Client.captcha ? "captcha.jpg" : ""
            }
            Button {
                id: loginButton
                anchors.right: parent.right
                text: i18n.tr("登录")

                onClicked: {
                    login(username.text, password.text, captcha.text);
                }
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

    function geCaptcha() {
        var url = "http://captcha.qq.com/getimage?" +
                "uin=" + QQ.Client.getInfo("uin") +
                "&vc_type=" + QQ.Client.getInfo("vc") +
                "&aid=" + QQ.Client.getInfo("aid") +
                "&r=" + Math.random();

        captchaImg.source = url;
    }

    function login(uin, password, vc) {
        var pwdMd5;

        if (vc.length === 0) {
            vc = QQ.Client.getInfo("vc");
        }
        //console.log(uinHex + ", " + password + ", " + vc);
        eval("var uinHex = '" + QQ.Client.getInfo("uinHex") + "'");
        pwdMd5 = MD5.pwdMd5(uinHex, password, vc);
        QQ.Client.login(uin, pwdMd5, vc);
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
