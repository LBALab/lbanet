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
// Generated from file `Stats.ice'
//
// Warning: do not edit this file.
//
// </auto-generated>


if(!interface_exists('Ice_Stats'))
{
    interface Ice_Stats
    {
        public function bytesSent($protocol, $num);
        public function bytesReceived($protocol, $num);
    }

    $Ice__t_Stats = IcePHP_defineClass('::Ice::Stats', 'Ice_Stats', true, $Ice__t_Object, null, null);
}
?>
