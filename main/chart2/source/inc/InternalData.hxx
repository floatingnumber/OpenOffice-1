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


#ifndef CHART2_INTERNALDATA_HXX
#define CHART2_INTERNALDATA_HXX

#include <com/sun/star/uno/Sequence.hxx>

#include <vector>
#include <valarray>

namespace chart
{

class InternalData
{
public:
    InternalData();

    void createDefaultData();

    void setData( const ::com::sun::star::uno::Sequence<
        ::com::sun::star::uno::Sequence< double > > & rDataInRows );
    ::com::sun::star::uno::Sequence<
        ::com::sun::star::uno::Sequence< double > > getData() const;

    ::com::sun::star::uno::Sequence< double > getColumnValues( sal_Int32 nColumnIndex ) const;
    ::com::sun::star::uno::Sequence< double > getRowValues( sal_Int32 nRowIndex ) const;

    void setColumnValues( sal_Int32 nColumnIndex, const ::std::vector< double > & rNewData );
    void setRowValues( sal_Int32 nRowIndex, const ::std::vector< double > & rNewData );

    void setComplexColumnLabel( sal_Int32 nColumnIndex, const ::std::vector< ::com::sun::star::uno::Any >& rComplexLabel );
    void setComplexRowLabel( sal_Int32 nRowIndex, const ::std::vector< ::com::sun::star::uno::Any >& rComplexLabel );

    ::std::vector< ::com::sun::star::uno::Any > getComplexColumnLabel( sal_Int32 nColumnIndex ) const;
    ::std::vector< ::com::sun::star::uno::Any > getComplexRowLabel( sal_Int32 nRowIndex ) const;
    
    void swapRowWithNext( sal_Int32 nRowIndex );
    void swapColumnWithNext( sal_Int32 nColumnIndex );

    void insertColumn( sal_Int32 nAfterIndex );
    void insertRow( sal_Int32 nAfterIndex );
    void deleteColumn( sal_Int32 nAtIndex );
    void deleteRow( sal_Int32 nAtIndex );

    /// @return the index of the newly appended column
    sal_Int32 appendColumn();
    /// @return the index of the newly appended row
    sal_Int32 appendRow();

    sal_Int32 getRowCount() const;
    sal_Int32 getColumnCount() const;

    typedef ::std::valarray< double > tDataType;
    typedef ::std::vector< ::std::vector< ::com::sun::star::uno::Any > > tVecVecAny; //inner index is hierarchical level

    void setComplexRowLabels( const tVecVecAny& rNewRowLabels );
    tVecVecAny getComplexRowLabels() const;
    void setComplexColumnLabels( const tVecVecAny& rNewColumnLabels );
    tVecVecAny getComplexColumnLabels() const;

#if OSL_DEBUG_LEVEL > 2
    void traceData() const;
#endif

private: //methods
    /** resizes the data if at least one of the given dimensions is larger than
        before.  The data is never becoming smaller only larger.

        @return </sal_True>, if the data was enlarged
    */
    bool enlargeData( sal_Int32 nColumnCount, sal_Int32 nRowCount );

private:
    sal_Int32   m_nColumnCount;
    sal_Int32   m_nRowCount;

    tDataType    m_aData;
    tVecVecAny   m_aRowLabels;//outer index is row index, inner index is category level
    tVecVecAny   m_aColumnLabels;//outer index is column index
};

#endif

} //  namespace chart
