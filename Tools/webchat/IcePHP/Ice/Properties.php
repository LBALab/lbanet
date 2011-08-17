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
// Generated from file `Properties.ice'
//
// Warning: do not edit this file.
//
// </auto-generated>

require 'Ice/BuiltinSequences.php';

if(!isset($Ice__t_PropertyDict))
{
    $Ice__t_PropertyDict = IcePHP_defineDictionary('::Ice::PropertyDict', $IcePHP__t_string, $IcePHP__t_string);
}

if(!interface_exists('Ice_Properties'))
{
    interface Ice_Properties
    {
        public function getProperty($key);
        public function getPropertyWithDefault($key, $value);
        public function getPropertyAsInt($key);
        public function getPropertyAsIntWithDefault($key, $value);
        public function getPropertyAsList($key);
        public function getPropertyAsListWithDefault($key, $value);
        public function getPropertiesForPrefix($prefix);
        public function setProperty($key, $value);
        public function getCommandLineOptions();
        public function parseCommandLineOptions($prefix, $options);
        public function parseIceCommandLineOptions($options);
        public function load($file);
        public function _clone();
    }

    $Ice__t_Properties = IcePHP_defineClass('::Ice::Properties', 'Ice_Properties', true, $Ice__t_Object, null, null);
}

if(!interface_exists('Ice_PropertiesAdmin'))
{
    interface Ice_PropertiesAdmin
    {
        public function getProperty($key);
        public function getPropertiesForPrefix($prefix);
    }

    class Ice_PropertiesAdminPrxHelper
    {
        public static function checkedCast($proxy, $facetOrCtx=null, $ctx=null)
        {
            return $proxy->ice_checkedCast('::Ice::PropertiesAdmin', $facetOrCtx, $ctx);
        }

        public static function uncheckedCast($proxy, $facet=null)
        {
            return $proxy->ice_uncheckedCast('::Ice::PropertiesAdmin', $facet);
        }
    }

    $Ice__t_PropertiesAdmin = IcePHP_defineClass('::Ice::PropertiesAdmin', 'Ice_PropertiesAdmin', true, $Ice__t_Object, null, null);

    $Ice__t_PropertiesAdminPrx = IcePHP_defineProxy($Ice__t_PropertiesAdmin);

    IcePHP_defineOperation($Ice__t_PropertiesAdmin, 'getProperty', 0, 0, array($IcePHP__t_string), null, $IcePHP__t_string, null);
    IcePHP_defineOperation($Ice__t_PropertiesAdmin, 'getPropertiesForPrefix', 0, 0, array($IcePHP__t_string), null, $Ice__t_PropertyDict, null);
}
?>
