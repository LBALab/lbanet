// **********************************************************************
//
// Copyright (c) 2003-2009 ZeroC, Inc. All rights reserved.
//
// This copy of Chat Demo is licensed to you under the terms described
// in the CHAT_DEMO_LICENSE file included in this distribution.
//
// **********************************************************************

#ifndef POLLING_CHAT_ICE
#define POLLING_CHAT_ICE

/**
 *
 * The PollingChat module define types and interfaces for polling clients
 * (PHP and Silverlight clients), which cannot use Glacier2 or callbacks.
 *
 **/
module LbaNet
{
	class ChatUserStatus
	{
	    /** The name of the user. */
	    string name;
	    
	    /** The color of the name. */    
	    string color;
	    
	    /** The status of the user. */ 	    
	    string status;
	};

	sequence<ChatUserStatus> UserSeq;


	/**
	 *
	 * ChatRoomEvent is an abstract base class used to model a union of
	 * possible event types.
	 *
	 **/
	class ChatRoomEvent
	{
	    /** The timestamp. */
	    long timestamp;
	    /** The name of the user. */
	    string name;
	};
	
	/**
	 *
	 * A sequence of state changes in the chat room.
	 *
	 * @see ChatRoomEvent
	 *
	 **/
	sequence<ChatRoomEvent> ChatRoomEventSeq;

	/**
	 *
	 * This event is generated when a user joins the chat room.
	 *
	 * @see ChatRoomEvent
	 *
	 **/
	class UserJoinedEvent extends ChatRoomEvent
	{
	};

	/**
	 *
	 * This event is generated when a user leaves the chat room.
	 *
	 * @see ChatRoomEvent
	 *
	 **/
	class UserLeftEvent extends ChatRoomEvent
	{
	};

	/**
	 *
	 * This event is generated when a user sends a message in the chat
	 * room.
	 *
	 * @see ChatRoomEvent
	 *
	 **/
	class MessageEvent extends ChatRoomEvent
	{
	    /** The contents of the message. */
	    string message;
	};
	
	/**
	 *
	 * This event is generated when a user change his status
	 *
	 * @see ChatRoomEvent
	 *
	 **/
	class UserStatusEvent extends ChatRoomEvent
	{
	    /** The color of the name. */    
	    string color;
	    
	    /** The status of the user. */ 	    
	    string status;	
	};	
	

	/**
	 *
	 * PollingChatSession is the session interface for polling clients.
	 *
	 **/
	interface PollingChatSession
	{
	    /**
	     *
	     * This operation returns a sequence of string with the names of
	     * the users in chat when this user connects. This function must
	     * be called when the session is created and before any call to
	     * getUpdates.
	     *
	     * @return The sequence of user names.
	     *
	     **/
	    ["ami"] UserSeq getInitialUsers();

	    /**
	     *
	     * This operation returns a sequence of ChatRoomEvent with the
	     * events that occured in the chat room since the last time the
	     * client called getUpdates.
	     *
	     * @return The sequence of chat room events.
	     *
	     **/
	    ["ami"] ChatRoomEventSeq getUpdates();

	    /**
	     *
	     * Send a message to the chat room.
	     *
	     * @param message The message to be sent.
	     *
	     * @return The time at which the message is sent.
	     *
	     * @throws InvalidMessageException should the message be invalid.
	     *
	     **/
	    ["ami"] long send(string message);

	    /**
	     *
	     * Destroy the session and leave the chat room.
	     *
	     **/
	    ["ami"] void destroy();
	};

	/**
	 *
	 * The CannotCreateSessionException indicates that a session could not be
	 * created, for example, because the user name contains an invalid character.
	 *
	 **/
	exception CannotCreateSessionException
	{
	    string reason;
	};

	/**
	 *
	 * Factory interface to create PollingChatSession objects.
	 *
	 **/
	interface PollingChatSessionFactory
	{
	    /**
	     *
	     * Create a new session and join the chat room.
	     *
	     **/
	    ["ami"] PollingChatSession* create(string name, string password) throws CannotCreateSessionException;
	};

};

#endif
