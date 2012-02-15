/**************************************************************
 * 
 * Licensed to the Apache Software Foundation (ASF) under one
 * or more contributor license agreements.  See the NOTICE file
 * distributed with this work for additional information
 * regarding copyright ownership.  The ASF licenses this file
 * to you under the Apache License, Version 2.0 (the
 * "License"); you may not use this file except in compliance
 * with the License.  You may obtain a copy of the License at
 * 
 *   http://www.apache.org/licenses/LICENSE-2.0
 * 
 * Unless required by applicable law or agreed to in writing,
 * software distributed under the License is distributed on an
 * "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY
 * KIND, either express or implied.  See the License for the
 * specific language governing permissions and limitations
 * under the License.
 * 
 *************************************************************/



#ifndef _SD_STLPROPERTYSET_HXX
#define _SD_STLPROPERTYSET_HXX

#include <com/sun/star/beans/PropertyValue.hpp>

#ifndef _UTL_STLTYPES_HXX_
#include <comphelper/stl_types.hxx>
#endif

#include <list>
#include <map>

namespace sd
{

const sal_Int32 STLPropertyState_DEFAULT = 0;
const sal_Int32 STLPropertyState_DIRECT = 1;
const sal_Int32 STLPropertyState_AMBIGUOUS = 3;

struct STLPropertyMapEntry
{
	::com::sun::star::uno::Any maValue;
	sal_Int32 mnState;

	STLPropertyMapEntry()
		: mnState( STLPropertyState_AMBIGUOUS ) {}
	STLPropertyMapEntry( ::com::sun::star::uno::Any aValue, sal_Int32 nState = STLPropertyState_DEFAULT )
		: maValue( aValue ), mnState( nState ) {}

};

typedef std::map<sal_Int32, STLPropertyMapEntry > PropertyMap;
typedef PropertyMap::iterator PropertyMapIter;
typedef PropertyMap::const_iterator PropertyMapConstIter;

class STLPropertySet
{
public:
	STLPropertySet();
	~STLPropertySet();

	void setPropertyDefaultValue( sal_Int32 nHandle, const com::sun::star::uno::Any& rValue );
	void setPropertyValue( sal_Int32 nHandle, const com::sun::star::uno::Any& rValue, sal_Int32 nState = STLPropertyState_DIRECT );
	::com::sun::star::uno::Any getPropertyValue( sal_Int32 nHandle ) const;

	sal_Int32 getPropertyState( sal_Int32 nHandle ) const;
	void setPropertyState( sal_Int32 nHandle, sal_Int32 nState );

private:
	bool findProperty( sal_Int32 nHandle, PropertyMapIter& rIter );
	bool findProperty( sal_Int32 nHandle, PropertyMapConstIter& rIter ) const;

private:
	PropertyMap maPropertyMap;
};

}

#endif // _SD_STLPROPERTYSET_HXX
