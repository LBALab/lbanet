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
// Generated from file `ObjectFactory.ice'
//
// Warning: do not edit this file.
//
// </auto-generated>


if(!interface_exists('Ice_ObjectFactory'))
{
    interface Ice_ObjectFactory
    {
        public function create($type);
        public function destroy();
    }

    $Ice__t_ObjectFactory = IcePHP_defineClass('::Ice::ObjectFactory', 'Ice_ObjectFactory', true, $Ice__t_Object, null, null);
}
?>
