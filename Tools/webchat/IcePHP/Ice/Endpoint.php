<?php
// **********************************************************************
//
// Copyright (c) 2003-2010 ZeroC, Inc. All rights reserved.
//
// This copy of Ice is licensed to you under the terms described in the
// ICE_LICENSE file included in this distribution.
//
// **********************************************************************

// Ice version 3.4.0

// <auto-generated>
//
// Generated from file `Endpoint.ice'
//
// Warning: do not edit this file.
//
// </auto-generated>

require 'Ice/BuiltinSequences.php';
require 'Ice/EndpointF.php';

if(!defined('Ice_TCPEndpointType'))
{
    define('Ice_TCPEndpointType', 1);
}

if(!defined('Ice_UDPEndpointType'))
{
    define('Ice_UDPEndpointType', 3);
}

if(!class_exists('Ice_EndpointInfo'))
{
    abstract class Ice_EndpointInfo
    {
        public function __construct($timeout=0, $compress=false)
        {
            $this->timeout = $timeout;
            $this->compress = $compress;
        }

        abstract public function type();
        abstract public function datagram();
        abstract public function secure();

        public function __toString()
        {
            global $Ice__t_EndpointInfo;
            return IcePHP_stringify($this, $Ice__t_EndpointInfo);
        }

        public $timeout;
        public $compress;
    }

    $Ice__t_EndpointInfo = IcePHP_defineClass('::Ice::EndpointInfo', 'Ice_EndpointInfo', true, $Ice__t_Object, null, array(
        array('timeout', $IcePHP__t_int),
    
        array('compress', $IcePHP__t_bool)));
}

if(!interface_exists('Ice_Endpoint'))
{
    interface Ice_Endpoint
    {
        public function toString();
        public function getInfo();
    }

    $Ice__t_Endpoint = IcePHP_defineClass('::Ice::Endpoint', 'Ice_Endpoint', true, $Ice__t_Object, null, null);
}

if(!class_exists('Ice_IPEndpointInfo'))
{
    abstract class Ice_IPEndpointInfo extends Ice_EndpointInfo
    {
        public function __construct($timeout=0, $compress=false, $host='', $port=0)
        {
            parent::__construct($timeout, $compress);
            $this->host = $host;
            $this->port = $port;
        }

        public function __toString()
        {
            global $Ice__t_IPEndpointInfo;
            return IcePHP_stringify($this, $Ice__t_IPEndpointInfo);
        }

        public $host;
        public $port;
    }

    $Ice__t_IPEndpointInfo = IcePHP_defineClass('::Ice::IPEndpointInfo', 'Ice_IPEndpointInfo', true, $Ice__t_EndpointInfo, null, array(
        array('host', $IcePHP__t_string),
    
        array('port', $IcePHP__t_int)));
}

if(!class_exists('Ice_TCPEndpointInfo'))
{
    abstract class Ice_TCPEndpointInfo extends Ice_IPEndpointInfo
    {
        public function __construct($timeout=0, $compress=false, $host='', $port=0)
        {
            parent::__construct($timeout, $compress, $host, $port);
        }

        public function __toString()
        {
            global $Ice__t_TCPEndpointInfo;
            return IcePHP_stringify($this, $Ice__t_TCPEndpointInfo);
        }
    }

    $Ice__t_TCPEndpointInfo = IcePHP_defineClass('::Ice::TCPEndpointInfo', 'Ice_TCPEndpointInfo', true, $Ice__t_IPEndpointInfo, null, null);
}

if(!class_exists('Ice_UDPEndpointInfo'))
{
    abstract class Ice_UDPEndpointInfo extends Ice_IPEndpointInfo
    {
        public function __construct($timeout=0, $compress=false, $host='', $port=0, $protocolMajor=0, $protocolMinor=0, $encodingMajor=0, $encodingMinor=0, $mcastInterface='', $mcastTtl=0)
        {
            parent::__construct($timeout, $compress, $host, $port);
            $this->protocolMajor = $protocolMajor;
            $this->protocolMinor = $protocolMinor;
            $this->encodingMajor = $encodingMajor;
            $this->encodingMinor = $encodingMinor;
            $this->mcastInterface = $mcastInterface;
            $this->mcastTtl = $mcastTtl;
        }

        public function __toString()
        {
            global $Ice__t_UDPEndpointInfo;
            return IcePHP_stringify($this, $Ice__t_UDPEndpointInfo);
        }

        public $protocolMajor;
        public $protocolMinor;
        public $encodingMajor;
        public $encodingMinor;
        public $mcastInterface;
        public $mcastTtl;
    }

    $Ice__t_UDPEndpointInfo = IcePHP_defineClass('::Ice::UDPEndpointInfo', 'Ice_UDPEndpointInfo', true, $Ice__t_IPEndpointInfo, null, array(
        array('protocolMajor', $IcePHP__t_byte),
    
        array('protocolMinor', $IcePHP__t_byte),
    
        array('encodingMajor', $IcePHP__t_byte),
    
        array('encodingMinor', $IcePHP__t_byte),
    
        array('mcastInterface', $IcePHP__t_string),
    
        array('mcastTtl', $IcePHP__t_int)));
}

if(!class_exists('Ice_OpaqueEndpointInfo'))
{
    abstract class Ice_OpaqueEndpointInfo extends Ice_EndpointInfo
    {
        public function __construct($timeout=0, $compress=false, $rawBytes=null)
        {
            parent::__construct($timeout, $compress);
            $this->rawBytes = $rawBytes;
        }

        public function __toString()
        {
            global $Ice__t_OpaqueEndpointInfo;
            return IcePHP_stringify($this, $Ice__t_OpaqueEndpointInfo);
        }

        public $rawBytes;
    }

    $Ice__t_OpaqueEndpointInfo = IcePHP_defineClass('::Ice::OpaqueEndpointInfo', 'Ice_OpaqueEndpointInfo', true, $Ice__t_EndpointInfo, null, array(
        array('rawBytes', $Ice__t_ByteSeq)));
}
?>
