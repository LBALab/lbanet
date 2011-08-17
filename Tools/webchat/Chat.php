<?php

// **********************************************************************
//
// Copyright (c) 2003-2009 ZeroC, Inc. All rights reserved.
//
// This copy of Chat Demo is licensed to you under the terms
// described in the CHAT_DEMO_LICENSE file included in this
// distribution.
//
// **********************************************************************


require_once 'Session.php';
require_once 'JSON.php';

//
// Encode the param $data as Json and send it to the client browser.
//
function printJson($data)
{
    $json = new Services_JSON();
    print($json->encode($data));
}

//
// Check that the Ice extension is loaded.
//
if(!extension_loaded("ice"))
{
    printJson("IcePHP extension is not loaded. Revise your IcePHP installation.");
    error_log("IcePHP extension is not loaded. Revise your IcePHP installation.");
    exit(1);
}

//
// Load the Chat profile.
//
Ice_loadProfile("IceChat");

//
// Ensure that `IceChat' profile was loaded or report an error.
//
if(!interface_exists("LbaNet_PollingChatSession"))
{
    printJson("IcePHP profile `IceChat' could not be loaded. Revise your IcePHP configuration for this chat demo.");
    error_log("IcePHP profile `IceChat' could not be loaded. Revise your IcePHP configuration for this chat demo.");
    exit(1);
}

//
// Disable session cookie.
//
//ini_set("session.use_cookies", false);

//
// Disable transid in urls.
//
//ini_set("session.session.use_transid", false);

//if(isset($_POST['id']))
//{
//    session_id($_POST['id']);
//}

//
// Disable caching
//
//header("Cache-Control: no-cache, must-revalidate"); // HTTP/1.1
//header("Expires: Sat, 26 Jul 1997 05:00:00 GMT"); // Date in the past

//
// Start the session, but do not report any PHP error to the client if it fails.
// There are exploits that use errors to get knowledge of web server backend internals
// and to search for other system vulnerabilities.
//
@session_start();
if(isset($_SESSION)) // Check that the session started OK
{
    try
    {
        //
        // Get the action from the post params.
        //
        $_action = isset($_POST['action']) ? $_POST['action'] : 'none';

        //
        // Create the session PHP object and pass a reference to $ICE.
        //
        $session = new Session($ICE);

        //
        // Process the action.
        //
        switch($_action)
        {
            case 'login':
            {
                $userName = stripslashes(isset($_POST['username']) ? $_POST['username'] : 'nobody');
                $userPassword = stripslashes(isset($_POST['password']) ? $_POST['password'] : 'nobody');
                printJson($session->login($userName, $userPassword));
                break;
            }
            case 'logout':
            {
                printJson($session->logout());
                break;
            }
            case 'send':
            {
                $message = stripslashes(isset($_POST['message']) ? $_POST['message'] : '');
                printJson($session->send($message));
                break;
            }
            case 'getUpdates':
            {
                printJson($session->getUpdates());
                break;
            }
            case 'getInitialUsers':
            {
                printJson($session->getInitialUsers());
                break;
            }
            default:
            {
                printJson("InvalidActionException");
                break;
            }
        }
    }
    catch(Exception $ex)
    {
        if(!isset($ex->jsontype))
        {
            error_log("Exception: " . $ex);
            $ex->jsontype = "Exception";
            printJson($ex);
        }
        else
        {
            printJson($ex);
        }
    }
}
else
{
    error_log("Error starting session");
    printJson($ex);
}
?>
