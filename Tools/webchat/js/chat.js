// **********************************************************************
//
// Copyright (c) 2003-2009 ZeroC, Inc. All rights reserved.
//
// This copy of Chat Demo is licensed to you under the terms
// described in the CHAT_DEMO_LICENSE file included in this
// distribution.
//
// **********************************************************************

var maxMessageSize = 1024;
var coordinator = 0;

// Replaces all instances of the given substring.
String.prototype.replaceAll = function(
					strTarget, // The substring you want to replace
					strSubString // The string you want to replace in.
					)
{
	var strText = this;
	var intIndexOfMatch = strText.indexOf( strTarget );
	var count = 0;

	// Keep looping while an instance of the target string
	// still exists in the string.
	while (intIndexOfMatch != -1)
	{
		// Relace out the current instance.
		strText = strText.replace( strTarget, strSubString )

		// Get the index of any next matching substring.
		intIndexOfMatch = strText.indexOf( strTarget );
		
		++count;
	}
 
	// Return the updated string with ALL the target strings
	// replaced out with the new substring.
	return {strText : strText, count : count};
}

String.prototype.trim = function()
{
    return this.replace(/^\s+|\s+$/g,"");
}

function formatDate(timestamp)
{
    date = new Date();
    date.setTime(timestamp);
    var dateStr = date.toLocaleTimeString().trim();
    var i = dateStr.indexOf(' ');
    if(i != -1)
    {
        dateStr = dateStr.substring(0, i);
    }
    return dateStr;
}

function formatUsername(name)
{
	return name;
}

function clearChilds(id)
{
    var childs = $(id).childElements();
    for(var i = 0; i < childs.length; i++)
    {
        childs[i].remove();
    }
}

function stripHtml(input)
{
    var output = "";
    for(var cont = 0; cont < input.length; cont++)
    {
        switch(input.charAt(cont))
        {
            case '&':
            {
                output += "&amp;";
                break;
            }

            case '"':
            {
                output += "&quot;";
                break;
            }

            case '\'':
            {
                output += "&#39;";
                break;
            }

            case '<':
            {
                output += "&lt;";
                break;
            }

            case '>':
            {
                output += "&gt;";
                break;
            }

            case '\r':
            case '\n':
            case '\f':
            case '\t':
            //case '\v': // Ie8 doesn't distigued between 'v' and '\v'
            {
                output += " ";
                break;
            }

            default:
            {
                output += input.charAt(cont);
                break;
            }
        }
    }
    return output;
}

function isNumber(o)
{
    return "number" == typeof o;
}

var Coordinator = Class.create(
{
    initialize:function(chatView)
    {
        this._chatView = chatView;
        this._updater = 0;
        this._init = false;
        this.setConnected(false);
        coordinator = this;
	 this._userscolor = new Hash();
    },

    login:function(name, password)
    {
        var username = name;
        
        var params = new Hash();
        params.set('action', 'login');
        params.set('username', name);
        params.set('password', password);

        var coordinator = this;
        var opts =
        {
            contentType:'application/x-www-form-urlencoded',
            method:'post',
            encoding:'UTF-8',
            parameters:params,
            onComplete:function(transport)
            {
                Element.hide('connectingContainer');
                Element.show('loginContainer');
                if(transport.status != 200)
                {
                    coordinator.setError("Connection with the web server failed:", "HTTP status code: " + transport.status);
                    $('txtUserName').focus();
                    return;
                }

                var response = transport.responseText.evalJSON(true);
                if( response.jsontype == 'Session')
                {
                    coordinator.setSessionId(response.id);
                    coordinator.setConnected(true);
                    coordinator._username = formatUsername(username);
		      coordinator._userscolor.set(username, 'FFFFFF');
                    return;
                }
                if(response.jsontype == "LbaNet_CannotCreateSessionException")
                {
                    coordinator._chatView.appendError("Login failed:", response.reason);
                    $('txtUserName').focus();
                    return;
                }
                if(response.jsontype == "Ice_UnknownLocalException")
                {
                    coordinator._chatView.appendError("Communication with server failed (Ice_UnknownLocalException)", response.unknown);
                    $('txtUserName').focus();
                    return;
                }
                coordinator._chatView.appendError("Communication with server failed:", transport.responseText);
                $('txtUserName').focus();
            }
        };
        new Ajax.Request('Chat.php', opts);
    },

    logout:function()
    {
        if(this.updater)
        {
            this.updater.stop();
            Chat.updater = 0;
        }
        var params = new Hash();
        params.set('id', this._sessionId);
        params.set('action','logout');
        var opts =
        {
            contentType:'application/x-www-form-urlencoded',
            method:'post',
            encoding:'UTF-8',
            parameters:params,
            onComplete: function(transport)
            {
            }
        };
        new Ajax.Request('Chat.php', opts);
        this.setConnected(false);
    },

    getInitialUsers:function()
    {
        if(coordinator._connected)
        {
            var params = new Hash();
            params.set('id', this._sessionId);
            params.set('action','getInitialUsers');
            var opts =
            {
                contentType:'application/x-www-form-urlencoded',
                method:'post',
                encoding:'UTF-8',
                parameters:params,
                onComplete:function(transport)
                {
                    if(transport.status != 200)
                    {
                        coordinator.connectionLost("<b>Connection with the web server failed: " + transport.status + "</b>");
                        return;
                    }
                    var response = transport.responseText.evalJSON(true);
                    if(response.jsontype !== undefined)
                    {
                        if(response.jsontype == "Ice_UnknownLocalException")
                        {
                            coordinator.connectionLost("(Ice_UnknownLocalException) " + response.unknown);
                            return;
                        }
                        coordinator.connectionLost(transport.responseText);
                        return;
                    }

                    if(!isNumber(response.length))
                    {
                        coordinator.connectionLost(transport.responseText);
                        return;
                    }

                    for(var i = 0; i < response.length; i++)
                    {
		        var txtuser = "<span style=\"color:#";
		        txtuser = txtuser + response[i].color.substring(2);              
		        txtuser = txtuser + "\">" + response[i].name;                        
		        if (response[i].status.length)
		        {
		         	txtuser = txtuser + " (" + response[i].status + ')';
		        }
		        txtuser = txtuser + "</span>";                    
                        var user = new Element('li', { 'id': '_' + response[i].name }).update(txtuser);
                        $('userList').insert(user);
                    }
                    coordinator._init = true;
                    coordinator.getUpdates();
                }
            }
            new Ajax.Request('Chat.php', opts);
        }
    },

    getUpdates:function()
    {
        if(!coordinator._connected || !coordinator._init)
        {
            return;
        }
        var params = new Hash();
        params.set('id', coordinator._sessionId);
        params.set('action','getUpdates');
        var opts =
        {
            contentType:'application/x-www-form-urlencoded',
            method:'post',
            encoding:'UTF-8',
            parameters:params,
            onComplete:function(transport)
            {

                if(!coordinator._connected)
                {
                    return;
                }
                if(transport.status != 200)
                {
                    coordinator.connectionLost("<b>Could not contact web server. HTTP status code: " + transport.status + "</b>");
                    return;
                }

                var response = transport.responseText.evalJSON(true);

                if(response.jsontype !== undefined)
                {
                    if(response.jsontype == "Ice_UnknownLocalException")
                    {
                        coordinator.connectionLost("(Ice_UnknownLocalException) " + response.unknown);
                        return;
                    }
                    coordinator.connectionLost(transport.responseText);
                    return;
                }

                if(!isNumber(response.length))
                {
                    coordinator.connectionLost(transport.responseText);
                    return;
                }

                for(var i = 0; i < response.length; i++)
                {
                    switch(response[i].jsontype)
                    {
                        case "LbaNet_UserJoinedEvent":
                            var user = new Element('li', { 'id': '_' + response[i].name }).update(response[i].name);
                            $('userList').insert(user);
                            coordinator._chatView.addMessage("<p>" + formatDate(response[i].timestamp) + " - &lt;system-message&gt; - "
                                    + response[i].name + " joined.</p>");
				coordinator._userscolor.set(response[i].name, 'FFFFFF');
                            break;

                        case "LbaNet_UserLeftEvent":
                            $('_' + response[i].name).remove();
                            coordinator._chatView.addMessage("<p>" + formatDate(response[i].timestamp) + " - &lt;system-message&gt; - "
                                    + response[i].name + " left.</p>");
				coordinator._userscolor.unset(response[i].name);			
                            break;

                        case "LbaNet_UserStatusEvent":
                            var txtuser = "<span style=\"color:#";
                            txtuser = txtuser + response[i].color.substring(2);    
                            txtuser = txtuser + "\">" + response[i].name;                        
                            if (response[i].status.length)
                            {
                            	txtuser = txtuser + " (" + response[i].status + ')';
                            }
                            txtuser = txtuser + "</span>";
                            $('_' + response[i].name).update(txtuser);    
				coordinator._userscolor.set(response[i].name, response[i].color.substring(2));                  
                            break;



                        case "LbaNet_MessageEvent":
                            if(response[i].name != coordinator._username)
                            {
                                coordinator._chatView.addMessage("<p>" + formatDate(response[i].timestamp) + " - <span style=\"color:#"
                                                                        + coordinator._userscolor.get(response[i].name)
                                                                        + "\">&lt;" + response[i].name + "&gt; </span>" + response[i].message
                                                                        + "</p>");
                            }
                            break;
 
                    }
                }
            }
        }
        new Ajax.Request('Chat.php', opts);
    },

    send:function(message)
    {
        
        var params = new Hash();
        var messageSend = message;
        params.set('id', this._sessionId);
        params.set('action','send');
        params.set('message',message);
        var opts =
        {
            contentType:'application/x-www-form-urlencoded',
            method:'post',
            encoding:'UTF-8',
            parameters:params,
            onComplete: function(transport)
            {

                if(transport.status != 200)
                {
                    coordinator.connectionLost("<b>Could not contact web server. HTTP status code: " + transport.status + "</b>");
                    return;
                }

                var response = transport.responseText.evalJSON(true);

                if(response.jsontype !== undefined)
                {
                    if(response.jsontype == "Chat_InvalidMessageException")
                    {
                        coordinator._chatView.addMessage("<p>&lt;system-message&gt; - " + response.reason + "</p>");
                        return;
                    }
                    if(response.jsontype == "Ice_UnknownLocalException")
                    {
                        coordinator.connectionLost("(Ice_UnknownLocalException) " + response.unknown);
                        return;
                    }
                    coordinator.connectionLost(transport.responseText);
                    return;
                }

                if(isNumber(parseInt(response)))
                {
                	if(messageSend.charAt(0) != '/')
                	{                                                                                                                    
			    coordinator._chatView.addMessage("<p>" + formatDate(response) + " - <span style=\"color:#"
								+ coordinator._userscolor.get(coordinator._username)
								+ "\">&lt;"
							    	+ coordinator._username + "&gt; </span>" + stripHtml(messageSend) +
							     "</p>");
                	}
			else
			{
				var currentTokens = messageSend.split( " " );
				if((currentTokens[0] == "/w") && (currentTokens.length > 2))
				{
					var messg = "";
					for ( var i = 2; i < currentTokens.length; i++ )
  					{
    						messg = messg + currentTokens[i];
  					}

			   		coordinator._chatView.addMessage("<p>" + formatDate(response) + " - to "
							    	+ currentTokens[1] + ": " + stripHtml(messg) +
							     "</p>");
				}
			}
                }
            }
        }
        new Ajax.Request('Chat.php', opts);
    },

    setError:function(error, info)
    {
        this.setConnected(false);
        this._chatView.appendError(error, info);
    },

    connectionLost:function(error)
    {
        if(this._connected)
        {
            warnOnBeforeUnload(false);
            this._connected = false;
            if(this._updater)
            {
                this._init = false;
                this._updater.stop();
                this._updater = 0;
            }
            this._chatView.connectionLost("<p>&lt;system-message&gt;The connection with " +
                                          "the server was unexpectedly lost.<br/>" + error +
                                          "<br/><b>Try to refresh the page.</b></p>");
        }
    },

    setConnected:function(connected)
    {
        this._connected = connected;
        if(connected)
        {
            this.getInitialUsers();
            this._updater = new PeriodicalExecuter(this.getUpdates, 3);
        }
        else
        {
            if(this._updater)
            {
                this._init = false;
                this._updater.stop();
                this._updater = 0;
            }
        }
        this._chatView.setConnected(connected);
    },

    setSessionId:function(sessionId)
    {
        this._sessionId = sessionId;
    }
});

var ChatView = Class.create(
{
    initialize:function()
    {
        this._coordinator = 0;
        this._state = "Offline";
    },

    setCoordinator:function(coordinator)
    {
        this._coordinator = coordinator;
    },

    login:function()
    {
        if(this._state == "Offline")
        {
            this._state = "Connecting";
            this.clearError();
            Element.hide('loginContainer');
            Element.show('connectingContainer');
            this._coordinator.login($('txtUserName').value, $('txtPassword').value);
        }
    },

    logout:function()
    {
        this._coordinator.logout();
        this._state = "Offline";
    },

    connectionLost:function(error)
    {
        warnOnBeforeUnload(false);
        statusBar('Offline');
        Element.hide('logoutLink');
        $('loginLink').show();
        var w = $('txtMessage').style.width;
        $('txtMessage').replace("<div id=\"txtMessage\"></div>");
        $('txtMessage').style.width = w;
        this.addMessage(error);
        this._state = "Offline";
    },

    setConnected:function(connected)
    {
        if(connected)
        {
            warnOnBeforeUnload(true);
            $('loginContainer').hide();
            $('conversationView').show();
            $('txtMessage').show();
            $('txtMessage').focus();
            this._state = "Online";
        }
        else
        {
            warnOnBeforeUnload(false);
            this.clearConversationView();
            Element.hide('connectingContainer');
            Element.hide('conversationView');
            $('loginContainer').show();
            this._state = "Offline";
        }
    },

    clearError:function()
    {
        clearChilds('errorView');
    },

    clearConversationView:function()
    {
        clearChilds('messageView');
        clearChilds('userList');
        $('txtMessage').value = "";
    },

    processInputEvent:function(event)
    {
        if(event.keyCode == 13)
        {
            message = $('txtMessage').value.trim();
            if(message != '')
            {
                if(message.length < maxMessageSize)
                {
                    this._coordinator.send(message);
                }
                else
                {
                    this.addMessage("<p>&lt;system-message&gt; - Message length exceeded, " +
                                                            "maximum length is " + maxMessageSize +
                                                            " characters. </p>");
                }
            }
            return false;
        }
        return true;
    },

    clearInputEvent:function(event)
    {
        if(event.keyCode == 13)
        {
            document.getElementById('txtMessage').value = "";
        }
    },

    appendError:function(name, info)
    {
        $('errorView').insert('<div><b>' + name + '</b></div>');
        $('errorView').insert('<div><i>' + info + '</i></div>');
        this._state = "Offline";
    },

    addMessage:function(message)
    {
   	var counto = 0;
    	var res = message.replaceAll("[red]", "<span style=\"color:red\">");
    	counto = counto + res.count;
     	var res = res.strText.replaceAll("[green]", "<span style=\"color:green\">");
    	counto = counto + res.count;   	
     	var res = res.strText.replaceAll("[blue]", "<span style=\"color:blue\">");
    	counto = counto + res.count;      	
     	var res = res.strText.replaceAll("[violet]", "<span style=\"color:violet\">");
    	counto = counto + res.count;        	
     	var res = res.strText.replaceAll("[cyan]", "<span style=\"color:cyan\">");
    	counto = counto + res.count;    
      	var res = res.strText.replaceAll("[yellow]", "<span style=\"color:yellow\">");
    	counto = counto + res.count;        	
     	var res = res.strText.replaceAll("[black]", "<span style=\"color:black\">");
    	counto = counto + res.count;     	
     	var res = res.strText.replaceAll("[white]", "<span style=\"color:white\">");
    	counto = counto + res.count;  

	//\[colour='\b[A-F0-9]{2}([A-F0-9]{6})\b']
	//<span style=\"color:#$1\">
	//var reg = new RegExp("(FF)", "g");
	//res.strText = res.strText.replace(reg, "plouf");
	
 	
 	var res = res.strText.replaceAll(":)", "<img src=\"images/smileys/smilie.png\" alt=\"\" align=\"middle\" border=\"0\">");
 	var res = res.strText.replaceAll(":-)", "<img src=\"images/smileys/smilie.png\" alt=\"\" align=\"middle\" border=\"0\">");
 	var res = res.strText.replaceAll(";)", "<img src=\"images/smileys/wink.png\" alt=\"\" align=\"middle\" border=\"0\">");
 	var res = res.strText.replaceAll(";-)", "<img src=\"images/smileys/wink.png\" alt=\"\" align=\"middle\" border=\"0\">");	
 	var res = res.strText.replaceAll(":/", "<img src=\"images/smileys/hmz.png\" alt=\"\" align=\"middle\" border=\"0\">");
 	var res = res.strText.replaceAll(":-/", "<img src=\"images/smileys/hmz.png\" alt=\"\" align=\"middle\" border=\"0\">");
 	var res = res.strText.replaceAll(":p", "<img src=\"images/smileys/tongue.png\" alt=\"\" align=\"middle\" border=\"0\">");
 	var res = res.strText.replaceAll(":-p", "<img src=\"images/smileys/tongue.png\" alt=\"\" align=\"middle\" border=\"0\">");
 	var res = res.strText.replaceAll(":P", "<img src=\"images/smileys/tongue.png\" alt=\"\" align=\"middle\" border=\"0\">");
 	var res = res.strText.replaceAll(":(", "<img src=\"images/smileys/frown.png\" alt=\"\" align=\"middle\" border=\"0\">");
 	var res = res.strText.replaceAll(":-(", "<img src=\"images/smileys/frown.png\" alt=\"\" align=\"middle\" border=\"0\">");	
 	var res = res.strText.replaceAll(":D", "<img src=\"images/smileys/biggrin.png\" alt=\"\" align=\"middle\" border=\"0\">");
 	var res = res.strText.replaceAll(":-D", "<img src=\"images/smileys/biggrin.png\" alt=\"\" align=\"middle\" border=\"0\">");	
 	var res = res.strText.replaceAll("|D", "<img src=\"images/smileys/proud.png\" alt=\"\" align=\"middle\" border=\"0\">");
 	var res = res.strText.replaceAll(":o", "<img src=\"images/smileys/embarrassment.png\" alt=\"\" align=\"middle\" border=\"0\">");
 	var res = res.strText.replaceAll(":x", "<img src=\"images/smileys/kiss.png\" alt=\"\" align=\"middle\" border=\"0\">");
 	var res = res.strText.replaceAll(":mad:", "<img src=\"images/smileys/mad.png\" alt=\"\" align=\"middle\" border=\"0\">");
 	var res = res.strText.replaceAll(":eek:", "<img src=\"images/smileys/eek.png\" alt=\"\" align=\"middle\" border=\"0\">");
 	var res = res.strText.replaceAll(":cool:", "<img src=\"images/smileys/cool.png\" alt=\"\" align=\"middle\" border=\"0\">");
 	var res = res.strText.replaceAll(":rolleyes:", "<img src=\"images/smileys/rolleyes.png\" alt=\"\" align=\"middle\" border=\"0\">");
 	var res = res.strText.replaceAll(":lol:", "<img src=\"images/smileys/lol.png\" alt=\"\" align=\"middle\" border=\"0\">");
 	var res = res.strText.replaceAll(":'(", "<img src=\"images/smileys/sad.png\" alt=\"\" align=\"middle\" border=\"0\">");		
 	var res = res.strText.replaceAll(":sad:", "<img src=\"images/smileys/sad.png\" alt=\"\" align=\"middle\" border=\"0\">");
 	var res = res.strText.replaceAll(":evilwink:", "<img src=\"images/smileys/evilwink.png\" alt=\"\" align=\"middle\" border=\"0\">");
 	var res = res.strText.replaceAll(":stupid:", "<img src=\"images/smileys/stupid.png\" alt=\"\" align=\"middle\" border=\"0\">");
 	var res = res.strText.replaceAll(":bloated:", "<img src=\"images/smileys/bloated.png\" alt=\"\" align=\"middle\" border=\"0\">");
 	var res = res.strText.replaceAll(":hmpf:", "<img src=\"images/smileys/hmpf.png\" alt=\"\" align=\"middle\" border=\"0\">");
 	var res = res.strText.replaceAll(":zombie:", "<img src=\"images/smileys/zombie.png\" alt=\"\" align=\"middle\" border=\"0\">");
 	var res = res.strText.replaceAll(":tup:", "<img src=\"images/smileys/tup.png\" alt=\"\" align=\"middle\" border=\"0\">");
 	var res = res.strText.replaceAll(":tdown:", "<img src=\"images/smileys/tdown.png\" alt=\"\" align=\"middle\" border=\"0\">");
 	var res = res.strText.replaceAll(":zoe:", "<img src=\"images/smileys/zoe.png\" alt=\"\" align=\"middle\" border=\"0\">");
 	var res = res.strText.replaceAll(":dino:", "<img src=\"images/smileys/dinofly.png\" alt=\"\" align=\"middle\" border=\"0\">");
 	var res = res.strText.replaceAll(":funfrock:", "<img src=\"images/smileys/funfrock.png\" alt=\"\" align=\"middle\" border=\"0\">");
	var res = res.strText.replaceAll(":bunny:", "<img src=\"images/smileys/rabibunny.png\" alt=\"\" align=\"middle\" border=\"0\">");
 
 
 
    	
    	for (var x = 0; x < counto; x++)
    	{
    		res.strText = res.strText + "</span>" + "\n";
    	}


        $('messageView').insert(res.strText);
        $('messageView').scrollTop = $('messageView').scrollHeight;
    }
});

var Chat = Class.create(
{
    initialize:function(chatView, loginname)
    {
        this._chatView = chatView;
        this._coordinator = new Coordinator(chatView);
        this._chatView.setCoordinator(this._coordinator);
        this._coordinator.login(loginname, "");
    }
});

function warnOnBeforeUnload(warn)
{
	//
	// Remove the event handler for on before unload event.
	//
	window.onbeforeunload = function ()
	    {
	    }.bind(this);
}

function passwordFocus(e)
{
    // if generated character code is equal to ascii 13 (if enter key)
    if(e.keyCode == 13)
    {
        $('txtPassword').focus();
        return false
    }
    else
    {
        return true
    }
}

function loginOnEnterPressed(chatView, e)
{
    // if generated character code is equal to ascii 13 (if enter key)
    if(e.keyCode == 13)
    {
        chatView.login();
        return false
    }
    else
    {
        return true
    }
}

function nosubmit()
{
    return false;
}

function statusBar(msg)
{
    var statusBar = new Element('p', { 'id': 'statusBar'}).update(msg);
    $('statusBar').replace(statusBar);
}

function focusId(id)
{
    try
    {
        $(id).focus();
    }
    catch(e)
    {
        // Don't report errors if focus cannot be set.
    }
}
