/***************************************************************************************************
 *
 * $ALPINE_TOOLKIT_BEGIN_LICENSE:GPL3$
 *
 * Copyright (C) 2017 Fabrice Salvaire
 * Contact: http://www.fabrice-salvaire.fr
 *
 * This file is part of the Alpine ToolKit software.
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 * $ALPINE_TOOLKIT_END_LICENSE$
 *
 **************************************************************************************************/

import QtQml 2.2
import QtQuick 2.6

import QtGraphicalEffects 1.0
import QtMultimedia 5.8
import QtQuick.Controls 2.0
import QtQuick.Controls.Material 2.2
import QtQuick.Layouts 1.1
import QtQuick.Window 2.2

import Constants 1.0
import Widgets 1.0 as Widgets

Widgets.Page {
    id: lamp_signal_pane

    Audio {
        id: player;
        playlist: Playlist {
            id: playlist
	    // PlaylistItem { source: "qrc:/tones/long-pulse.ogg"; }
        }
    }

    function play_message(encoded_message)
    {
	// encoded_message = '...././.-../.-../---'
	console.info('set_playlist: ' + encoded_message);
	playlist.clear();
	for (var i = 0; i < encoded_message.length; i++) {
	    if (i > 0)
		playlist.addItem('qrc:/tones/short-pause.ogg');
	    var c = encoded_message[i];
	    if (c == '.')
		playlist.addItem('qrc:/tones/short-pulse.ogg');
	    else if (c == '-')
		playlist.addItem('qrc:/tones/long-pulse.ogg');
	    else if (c == '/')
		playlist.addItem('qrc:/tones/long-pause.ogg');
	}
	player.play();
    }

    SwipeView {
        id: swipe_view
        currentIndex: 0
        width: parent.width
        anchors.top: parent.top
        anchors.bottom: page_indicator.top

	// SwipeView takes over the geometry management of items added

        Pane {
            id: send_message_pane

	    Flickable {
		anchors.fill: parent
                anchors.margins: Style.spacing.base
		contentHeight: send_message_content.height
		clip: true

		Column {
		    id: send_message_content
		    width: parent.width
                    spacing: Style.spacing.base

                    Label {
			id: help_message
			width: parent.width
			wrapMode:Text.WordWrap
			text: qsTr('<b>Use preferably number and latin alphabet without diacritic.</b>')
			// <br>Despite International Morse Code has a larger support.'
			// Fixme: show morse code table
                    }

		    TextArea {
		    	id: message_textarea
		    	width: parent.width
		    	placeholderText: qsTr('Enter message')
			wrapMode: Text.WrapAnywhere
                    }

                    Label {
		    	id: send_encoded_message
		    	width: parent.width
		    	wrapMode: Text.WrapAnywhere
                    }

		    Row {
		    	anchors.horizontalCenter: parent.horizontalCenter
		    	spacing: Style.spacing.base

		    	ToolButton {
		    	    id: torch_switch
		    	    checkable: true
		    	    width: swipe_view.width / 6
		    	    height: width

		    	    contentItem: Item {
		    		width: torch_switch.size
		    		height: torch_switch.width

		    		Image {
		    		    id: light_bulb_icon
		    		    source: 'qrc:/icons/light-bulb-white.svg'
		    		    sourceSize: Qt.size(parent.width, parent.height)
		    		    visible: false
		    		}

		    		// Fixme: don't work with black qtgraphicaleffects/src/effects/shaders/coloroverlay.frag
		    		ColorOverlay {
		    		    anchors.fill: light_bulb_icon
		    		    source: light_bulb_icon
		    		    color: torch_switch.checked ? Material.color(Material.Green) : 'black' // '#2bc82b'
		    		}
		    	    }
		    	}

		    	ToolButton {
		    	    id: speaker_switch
		    	    checkable: true
		    	    width: swipe_view.width / 6
		    	    height: width

		    	    contentItem: Item {
		    		width: speaker_switch.size
		    		height: speaker_switch.width

		    		Image {
		    		    id: speaker_icon
		    		    source: 'qrc:/icons/volume-white.svg'
		    		    sourceSize: Qt.size(parent.width, parent.height)
		    		    visible: false
		    		}

		    		// Fixme: don't work with black qtgraphicaleffects/src/effects/shaders/coloroverlay.frag
		    		ColorOverlay {
		    		    anchors.fill: speaker_icon
		    		    source: speaker_icon
		    		    color: speaker_switch.checked ? Material.color(Material.Green) : 'black' // '#2bc82b'
		    		}
		    	    }
		    	}
		    }

                    Row {
		    	id: rate_box
		    	anchors.horizontalCenter: parent.horizontalCenter
		    	spacing: Style.spacing.base
		    	Label {
                            anchors.verticalCenter: parent.verticalCenter
                            text: qsTr('rate')
		    	}
		    	SpinBox {
                            id: rate_ms_spinbox
                            from: 50
                            to: 1000
                            stepSize: 50
                            value: 250
		    	}
		    	Label {
                            anchors.verticalCenter: parent.verticalCenter
                            text: qsTr('ms')
		    	}
                    }

                    Button {
		    	id: send_button
		    	anchors.horizontalCenter: parent.horizontalCenter
		    	text: qsTr('Send Message')
		    	onClicked : {
                            var message = message_textarea.text;
                            if (message) {
		    		var encoded_message = application.encode_morse(message, false);
		    		send_encoded_message.text = encoded_message;
                                if (speaker_switch.checked)
		    		    play_message(encoded_message);
                                if (torch_switch.checked) {
		    		    var encoded_message = application.encode_morse(message, true);
		    		    var rate_ms = rate_ms_spinbox.value;
		    		    platform_abstraction.perform_lamp_signal(encoded_message, rate_ms);
                                }
                            }
		    	}
                    }
		}

		ScrollBar.vertical: ScrollBar { }
            }
	}

        Pane {
            id: message_decoder_pane

	    function decode_message() {
		var _encoded_message = encoded_message.text;
		if (_encoded_message) {
                    var raw_message = application.decode_morse(_encoded_message);
                    var message = raw_message.slice(0, raw_message.length - 2);
                    if (raw_message.endsWith('@F'))
                        message += ' <span style="color:#F44336">[ERROR]</span>'
                    decoded_message.text = message
                }
	    }

	    Flickable {
		anchors.fill: parent
                anchors.margins: Style.spacing.base
		contentHeight: message_decoder_content.height
		clip: true

		Column {
		    id: message_decoder_content
		    width: parent.width
                    spacing: Style.spacing.base

                    Label {
			id: title
			anchors.horizontalCenter: parent.horizontalCenter
			// wrapMode:Text.WordWrap
			text: qsTr('<h1>Morse Code Decoder<h1>') // International
                    }

                    GridLayout {
			id: button_layout
			anchors.horizontalCenter: parent.horizontalCenter
			Layout.alignment: Qt.AlignCenter
			columns: 2
			columnSpacing : Style.spacing.base
			rowSpacing : Style.spacing.base

			Button {
                            // Fixme: duplicated code ...
                            implicitWidth: message_decoder_content.width * .4
                            padding : 20
                            font.pointSize: Style.font_size.large
                            text: qsTr('Dot')
                            onClicked: encoded_message.text += '.'
			}
			Button {
                            implicitWidth: message_decoder_content.width * .4
                            padding : 20
                            font.pointSize: Style.font_size.large
                            text: qsTr('Dash')
                            onClicked: encoded_message.text += '-'
			}
			Button {
                            implicitWidth: message_decoder_content.width * .4
                            padding : 20
                            font.pointSize: Style.font_size.large
                            text: qsTr('Letter')
                            onClicked: {
				encoded_message.text += '/';
				message_decoder_pane.decode_message();
                            }
			}
			Button {
                            implicitWidth: message_decoder_content.width * .4
                            padding : 20
                            font.pointSize: Style.font_size.large
                            text: qsTr('Word')
                            onClicked: {
				encoded_message.text += ' ';
				message_decoder_pane.decode_message();
                            }
			}
                    }

                    Label {
			id: encoded_message
			width: parent.width
                        padding: Style.spacing.base
                        background: Rectangle {
                            color: Material.color(Material.Grey, Material.Shade200)
                        }
                    }

                    Label {
			id: decoded_message
			width: parent.width
                        padding: Style.spacing.base
                        textFormat: Text.RichText
                        background: Rectangle {
                            color: Material.color(Material.Grey, Material.Shade200)
                        }
                    }

                    Button {
			id: delete_button
			anchors.horizontalCenter: parent.horizontalCenter
			text: qsTr('Delete')
			onClicked : {
                            var message = encoded_message.text;
                            if (message) {
                                var new_message = message.slice(0, message.length -1);
				encoded_message.text = new_message;
                                if (new_message.endsWith(' ') || new_message.endsWith('/'))
				    message_decoder_pane.decode_message();
                                // Fixme: cursor is not visible
                            }
			}
                    }

                    Button {
			id: clear_button
			anchors.horizontalCenter: parent.horizontalCenter
			text: qsTr('Clear Message')
			onClicked : {
                            encoded_message.text = ''
                            decoded_message.text = ''
			}
                    }
		}

		ScrollBar.vertical: ScrollBar { }
            }
	}
    }

    PageIndicator {
        id: page_indicator
        anchors.bottom: parent.bottom
        anchors.horizontalCenter: parent.horizontalCenter
        count: swipe_view.count
        currentIndex: swipe_view.currentIndex
    }
}
