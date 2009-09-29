/* -*- Mode: C++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*- */
/* ***** BEGIN LICENSE BLOCK *****
 * Copyright (C) 1998, 2009 the Initial Developer and contributors.
 * All rights reserved.
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 * The Original Code is mozilla.org code.
 *
 * The Initial Developer of the Original Code is
 * Netscape Communications Corporation.
 * Portions created by the Initial Developer are Copyright (C) 1998
 * the Initial Developer. All Rights Reserved.
 *
 * Contributor(s):
 * Portions Copyright (c) 2009, 3Di, Inc. (http://3di.jp/).
 * All Rights Reserved.
 *
 * ***** END LICENSE BLOCK ***** */

// ==============================
// ! Scriptability related code !
// ==============================
//
// nsScriptablePeer - xpconnect scriptable peer
//

#ifndef __nsScriptablePeer_h__
#define __nsScriptablePeer_h__

#include "nsIScriptablePlugin.h"
#include "nsIClassInfo.h"
#include "nsIProgrammingLanguage.h"

class nsPluginInstance;

// We must implement nsIClassInfo because it signals the
// Mozilla Security Manager to allow calls from JavaScript.

class nsClassInfoMixin : public nsIClassInfo
{
  // These flags are used by the DOM and security systems to signal that 
  // JavaScript callers are allowed to call this object's scritable methods.
  NS_IMETHOD GetFlags(PRUint32 *aFlags)
    {*aFlags = nsIClassInfo::PLUGIN_OBJECT | nsIClassInfo::DOM_OBJECT;
     return NS_OK;}
  NS_IMETHOD GetImplementationLanguage(PRUint32 *aImplementationLanguage)
    {*aImplementationLanguage = nsIProgrammingLanguage::CPLUSPLUS;
     return NS_OK;}
  // The rest of the methods can safely return error codes...
  NS_IMETHOD GetInterfaces(PRUint32 *count, nsIID * **array)
    {return NS_ERROR_NOT_IMPLEMENTED;}
  NS_IMETHOD GetHelperForLanguage(PRUint32 language, nsISupports **_retval)
    {return NS_ERROR_NOT_IMPLEMENTED;}
  NS_IMETHOD GetContractID(char * *aContractID)
    {return NS_ERROR_NOT_IMPLEMENTED;}
  NS_IMETHOD GetClassDescription(char * *aClassDescription)
    {return NS_ERROR_NOT_IMPLEMENTED;}
  NS_IMETHOD GetClassID(nsCID * *aClassID)
    {return NS_ERROR_NOT_IMPLEMENTED;}
  NS_IMETHOD GetClassIDNoAlloc(nsCID *aClassIDNoAlloc)
    {return NS_ERROR_NOT_IMPLEMENTED;}
};

class nsScriptablePeer : public nsIScriptablePlugin,
                         public nsClassInfoMixin
{
public:
  nsScriptablePeer(nsPluginInstance* plugin);
  ~nsScriptablePeer();

public:
  // methods from nsISupports
  NS_IMETHOD QueryInterface(const nsIID& aIID, void** aInstancePtr); 
  NS_IMETHOD_(nsrefcnt) AddRef(); 
  NS_IMETHOD_(nsrefcnt) Release(); 

protected: 
  nsrefcnt mRefCnt;  

public:
  // native methods callable from JavaScript
  NS_DECL_NSISCRIPTABLEPLUGIN

  void SetInstance(nsPluginInstance* plugin);
  nsPluginInstance* GetInstance();

protected:
  nsPluginInstance* mPlugin;
};

#endif
