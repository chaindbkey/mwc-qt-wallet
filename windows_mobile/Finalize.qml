import QtQuick 2.0
import QtQuick.Controls 2.13
import Qt.labs.platform 1.1
import QtQuick.Window 2.0
import FinalizeBridge 1.0
import ConfigBridge 1.0
import UtilBridge 1.0

Item {
    FinalizeBridge {
        id: finalize
    }

    ConfigBridge {
        id: config
    }

    UtilBridge {
        id: util
    }

    function slatepackCallback(ok, slatepack, slateJson, sender) {
        if (ok) {
            finalize.uploadSlatepackTransaction(slatepack, slateJson, sender)
        }
    }

    Image {
        id: image_finalize
        width: dp(80)
        height: dp(80)
        anchors.bottom: text_finalize.top
        anchors.bottomMargin: dp(30)
        anchors.horizontalCenter: parent.horizontalCenter
        fillMode: Image.PreserveAspectFit
        source: "../img/FinalizeL@2x.svg"
    }

    Text {
        id: text_finalize
        color: "#ffffff"
        text: qsTr("Finalize Transaction")
        anchors.verticalCenterOffset: dp(-100)
        anchors.verticalCenter: parent.verticalCenter
        anchors.horizontalCenter: parent.horizontalCenter
        font.pixelSize: dp(25)
    }

    Button {
        id: button_upload
        width: dp(250)
        height: dp(50)
        anchors.verticalCenter: parent.verticalCenter
        anchors.horizontalCenter: parent.horizontalCenter
        background: Rectangle {
            color: "#00000000"
            radius: dp(4)
            border.color: "white"
            border.width: dp(2)
            Text {
                text: qsTr("Upload a File")
                anchors.verticalCenter: parent.verticalCenter
                anchors.horizontalCenter: parent.horizontalCenter
                font.pixelSize: dp(18)
                color: "white"
            }
        }

        onClicked: {
            if (!finalize.isNodeHealthy()) {
                messagebox.open(qsTr("Unable to finalize"), qsTr("Your MWC Node, that wallet connected to, is not ready to finalize transactions.\nMWC Node need to be connected to few peers and finish blocks synchronization process"))
                return
            }
            fileDialog.open()
        }
    }

    Button {
        id: button_slatepack
        width: dp(250)
        height: dp(50)
        anchors.verticalCenterOffset: dp(100)
        anchors.verticalCenter: parent.verticalCenter
        anchors.horizontalCenter: parent.horizontalCenter
        background: Rectangle {
            color: "#00000000"
            radius: dp(4)
            border.color: "white"
            border.width: dp(2)
            Text {
                text: qsTr("Paste Slatepack")
                anchors.verticalCenter: parent.verticalCenter
                anchors.horizontalCenter: parent.horizontalCenter
                font.pixelSize: dp(18)
                color: "white"
            }
        }

        onClicked: {
            inputSlatepack.open("SendResponse", "Send response slate", 2, slatepackCallback)
        }
    }


    FileDialog {
        id: fileDialog
        title: qsTr("Finalize transaction file")
        folder: config.getPathFor("fileGen")
        nameFilters: ["MWC response transaction (*.tx.response *.response);;All files (*.*)"]
        onAccepted: {
            var path = fileDialog.file.toString()

            const validation = util.validateMwc713Str(path)
            if (validation) {
                messagebox.open(qsTr("File Path"), qsTr("This file path is not acceptable.\n" + validation))
                return
            }
            // remove prefixed "file:///"
            path= path.replace(/^(file:\/{3})|(qrc:\/{2})|(http:\/{2})/,"")
            // unescape html codes like '%23' for '#'
            const cleanPath = decodeURIComponent(path);
            let filePath = cleanPath
            if(cleanPath.search("Download/") > 0) {
                filePath = downloadPath + cleanPath.substring(cleanPath.search("Download/") + 8, cleanPath.length)
            }
            config.updatePathFor("fileGen", filePath)
            finalize.uploadFileTransaction(filePath);
        }
    }
}
