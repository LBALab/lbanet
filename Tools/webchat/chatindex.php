<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN"
    "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">

<html xmlns="http://www.w3.org/1999/xhtml" xml:lang="en">

<head>
<meta http-equiv="content-type" content="text/html; charset=utf-8" />



<title>Chat PHP Client</title>

<link rel="stylesheet" href="resources/style.css" type="text/css" media="screen"/>

<script src="js/prototype.js" type="text/javascript"></script>
<script src="js/chat.js" type="text/javascript"></script>

<script type="text/javascript">

    //
    // This method is a handler for window.onreszize event.
    // It is called when the window is resized to adjust
    // the size of the chat interface.
    //
    function adjustSize()
    {
        var minHeight = 440;
        var h = $('body').getHeight();
        if(h < minHeight)
        {
            h = minHeight;
        }
        $('livechat').style.height = h + 'px';
        $('chatcontent').style.height = (h - 69) + 'px';
        $('conversationView').style.height = (h - 69) + 'px';
        $('userList').style.height = (h - 102) + 'px';
        $('messageView').style.height = (h - 102) + 'px';

        var minWidth = 400;
        var w = $('body').getWidth();
        if(w < minWidth)
        {
            w = minWidth;
        }

        $('livechat').style.width = (w) + 'px';
        $('txtMessage').style.width = (w - 20) + 'px';
        $('messageView').style.width = (w - 165) + 'px';
        $('messageView').scrollTop = $('messageView').scrollHeight;
    }

    window.onresize = function()
    {
        adjustSize();
    }

    //
    // The application calls this to return to the login form
    // when the connection is lost.
    //
    // It reloads the main page and shows the login form.
    //
    function reloadPage()
    {
        var pos = window.location.href.lastIndexOf("/");
        var loc = window.location.href;
        if(pos > 0)
        {
            loc = location.href.substr(0, pos)
        }
        window.location.href = loc + "/chatindex.php";
    }

    var chatView;
    var chat;

    //
    // This operation initializes the chat interface.
    //
    function initialize(username)
    {
        var opts =
        {
            encoding:'UTF-8',
            method: 'get',
            parameters: '',
            asynchronous: false ,
            onComplete:function(response)
            {
                $('loadingContainer').hide();
                $('jsSupportError').replace(response.responseText);
                adjustSize();
            }
        }
        new Ajax.Request("chatview.html",opts);
        chatView = new ChatView();
        chat = new Chat(chatView, username);
    }
</script>
</head>



<?php
ini_set( "display_errors", 0);
define( '_JEXEC', 1 );
define('JPATH_BASE', dirname(__FILE__) );
define( 'DS', DIRECTORY_SEPARATOR );
require_once ( JPATH_BASE .DS.'includes'.DS.'defines.php' );
require_once ( JPATH_BASE .DS.'includes'.DS.'framework.php' );
	$mainframe =& JFactory::getApplication('site');
	$user =& JFactory::getUser();
	if($user && !empty($user->username))
		echo "<body id=\"body\" onload=\"initialize('(w)".$user->username."');\">";
	else
		echo "<body id=\"body\" >";
?>

    <div id="livechat">

        <!-- Main Content begin -->
        <div id="chatcontent">
            <div id="loadingContainer">
                <div id="connecting">Loading</div>
            </div>
            <div id="jsSupportError">
                Your browser's JavaScript support is not enabled or your browser is not
                compatible with the Prototype JavaScript library required by this chat.
            </div>
            <script type="text/javascript">
                // This hides the JavaScript error message, using prototype JavaScript library,
                // so if JavaScript isn't enabled or prototype doesn't work the error message
                // is displayed.
                $('jsSupportError').hide();
                $('loadingContainer').style.display = "block";
            </script>

        </div>

    </div>


</body>
</html>
