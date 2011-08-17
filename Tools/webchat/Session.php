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

class JavaScriptSession
{
    public $jsontype;
    public $id;

    function __construct($id)
    {
        $this->id = $id;
        $this->jsontype = "Session";
    }
}

/**
 *
 * The Session class holds the proxy to the PollingChatSession and permits
 * interaction with the chat room.
 *
 **/

class Session
{
    private $_ice = 0;
    private $_chatsession = 0;

    //
    // Constructor
    //
    function __construct($ice)
    {
        $this->_ice = $ice;

        if($this->isConnected())
        {
            $this->_chatsession = $this->_ice->stringToProxy($_SESSION["chatsession"]);
            $this->_chatsession = $this->_chatsession->ice_uncheckedCast("::LbaNet::PollingChatSession");
        }
    }

    //
    // Join the chat.
    //
    function login($username, $password)
    {
        try
        {
            //
            // Initialize a proxy to the PollingChatSessionFactory.
            //
            $chatsessionfactory = $this->_ice->stringToProxy("PollingChatServer1-ChatSessionFactory");

            //
            // Cast the proxy to the appropriate type.
            //
            $chatsessionfactory = $chatsessionfactory->ice_uncheckedCast("::LbaNet::PollingChatSessionFactory");

            //
            // Create a new session.
            //
            $this->_chatsession = $chatsessionfactory->create($username, $password);

            //
            // Mark the PHP session as connected.
            //
            $this->setConnected(true);

            return new JavaScriptSession(session_id()); // Return the sessionId to the client.
        }
        catch(Ice_Exception $ex)
        {
            $ex->jsontype = get_class($ex);
            return $ex;
        }
    }

    //
    // Leave the chat.
    //
    function logout()
    {
        if($this->isConnected())
        {
            try
            {
                $this->_chatsession->destroy();
            }
            catch(Ice_Exception $ex)
            {
            }
            $this->setConnected(false);
        }
    }

    //
    // Send a message to the chat.
    //
    function send($message)
    {
        $this->checkIsConnected();
        try
        {
            return $this->_chatsession->send($message);
        }
        catch(Ice_Exception $ex)
        {
            $ex->jsontype = get_class($ex);
            return $ex;
        }
    }

    //
    // Get the initial set of users in the chat room.
    //
    function getInitialUsers()
    {
        $this->checkIsConnected();
        try
        {
            return $this->_chatsession->getInitialUsers();
        }
        catch(Ice_Exception $ex)
        {
            $ex->jsontype = get_class($ex);
            return $ex;
        }
    }

    //
    // Get state changes in the room since the previous call.
    //
    function getUpdates()
    {
        $this->checkIsConnected();
        try
        {
            $updates = $this->_chatsession->getUpdates();
            foreach($updates as $update)
            {
                $update->jsontype = get_class($update);
            }
            return $updates;
        }
        catch(Ice_Exception $ex)
        {
            $ex->jsontype = get_class($ex);
            return $ex;
        }
    }

    //
    // Set the status of the session.
    //
    function setConnected($connected)
    {
        if($connected)
        {
            //
            // Save the session proxy to the PHP $_SESSION object as a string proxy.
            //
            $_SESSION["chatsession"] = $this->_ice->proxyToString($this->_chatsession);

            //
            // Set the connected flag to true (Connected).
            //
            $_SESSION["connected"] = "true";
        }
        else
        {
            //
            // Set the connected flag to false (Disconnected)
            //
            $_SESSION["connected"] = "false";

            //
            // Erase the chatsession string proxy.
            //
            $_SESSION["chatsession"] = "";

            //
            // Erase the reference to the chatsession proxy.
            //
            $this->_chatsession = 0;
        }
    }

    //
    // Helper method to check if a user is connected. Return true if connected,
    // false otherwise.
    //
    function isConnected()
    {
        return isset($_SESSION["connected"]) && $_SESSION["connected"] == "true";
    }

    //
    // This method checks if the user is connected. If the user is not connected,
    // it raises Ice_ObjectNotExistException; otherwise, it does nothing.
    //
    function checkIsConnected()
    {
        if(!$this->isConnected())
        {
            $ex = new Ice_ObjectNotExistException();
            $ex->jsontype = get_class($ex);
            throw $ex;
        }
    }
}
?>
