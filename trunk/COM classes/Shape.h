// ********************************************************************************************************
// File name: Shape.h
// Description: Declaration of the CShape
// ********************************************************************************************************
// The contents of this file are subject to the Mozilla Public License Version 1.1 (the "License"); 
// you may not use this file except in compliance with the License. You may obtain a copy of the License at 
// http://www.mozilla.org/MPL/ 
// Software distributed under the License is distributed on an "AS IS" basis, WITHOUT WARRANTY OF 
// ANY KIND, either express or implied. See the License for the specificlanguage governing rights and 
// limitations under the License. 
//
// The Original Code is MapWindow Open Source. 
//
// The Initial Developer of this version of the Original Code is Daniel P. Ames using portions created by 
// Utah State University and the Idaho National Engineering and Environmental Lab that were released as 
// public domain in March 2004.  
//
// -------------------------------------------------------------------------------------------------------
// Contributor(s): (Open source contributors should list themselves and their modifications here). 

#pragma once
#include "MapWinGis.h"
#include <comsvcs.h>
#include <deque>
#include <vector>
#include <algorithm>

#include "ShapeInterfaces.h"
#include "GeometryConverter.h"
#include "ShapeWrapper.h"
#include "ShapeWrapperCOM.h"
#include "ShapePoint.h"

// ******************************************************
//	 CShape declaration
// ******************************************************
class ATL_NO_VTABLE CShape : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CShape, &CLSID_Shape>,
	public IDispatchImpl<IShape, &IID_IShape, &LIBID_MapWinGIS, /*wMajor =*/ VERSION_MAJOR, /*wMinor =*/ VERSION_MINOR>
{
public:
	CShape()
	{	
		USES_CONVERSION;
		_key = A2BSTR("");
		_globalCallback = NULL;
		_lastErrorCode = tkNO_ERROR;
		_isValidReason = "";
		
		//_useFastMode = false;	// equal to false by default
		//						// the usage of wrapper can be set through shapefile only;
		//						// in that case when inserting new shape into the shapefile,
		//						// point objects will be converted to the wrapper class

		_useFastMode = m_globalSettings.shapefileFastMode;
		if (m_globalSettings.shapefileFastMode)
		{
			_shp = new CShapeWrapper(SHP_NULLSHAPE);
		}
		else
		{
			_shp = new CShapeWrapperCOM(SHP_NULLSHAPE);
		}
	}
	
	// destructor
	~CShape()
	{
		::SysFreeString(_key);			
			
		if (_shp)
		{
			if (_useFastMode)
			{
				delete (CShapeWrapper*)_shp;
			}
			else
			{
				delete (CShapeWrapperCOM*)_shp;
			}
			_shp = NULL;
		}

		if (_globalCallback)
		{
			_globalCallback->Release();
		}
	}

	DECLARE_PROTECT_FINAL_CONSTRUCT()

	HRESULT FinalConstruct()
	{
		return S_OK;
	}
	
	void FinalRelease() 
	{
	}

	DECLARE_REGISTRY_RESOURCEID(IDR_SHAPE)

	DECLARE_NOT_AGGREGATABLE(CShape)

	BEGIN_COM_MAP(CShape)
		COM_INTERFACE_ENTRY(IShape)
		COM_INTERFACE_ENTRY(IDispatch)
	END_COM_MAP()

// ******************************************************
//	 IShape interface
// ******************************************************
public:
	STDMETHOD(get_Extents)(/*[out, retval]*/ IExtents * *pVal);
	STDMETHOD(DeletePart)(/*[in]*/ long PartIndex, /*[out, retval]*/ VARIANT_BOOL * retval);
	STDMETHOD(InsertPart)(/*[in]*/ long PointIndex, /*[in, out]*/ long * PartIndex, /*[out, retval]*/ VARIANT_BOOL * retval);
	STDMETHOD(DeletePoint)(/*[in]*/ long PointIndex, /*[out, retval]*/ VARIANT_BOOL * retval);
	STDMETHOD(InsertPoint)(/*[in]*/ IPoint * NewPoint, /*[in, out]*/long * PointIndex, /*[out, retval]*/ VARIANT_BOOL * retval);
	STDMETHOD(Create)(/*[in]*/ ShpfileType _shptype, /*[out, retval]*/ VARIANT_BOOL * retval);
	STDMETHOD(get_Key)(/*[out, retval]*/ BSTR *pVal);
	STDMETHOD(put_Key)(/*[in]*/ BSTR newVal);
	STDMETHOD(get_GlobalCallback)(/*[out, retval]*/ ICallback * *pVal);
	STDMETHOD(put_GlobalCallback)(/*[in]*/ ICallback * newVal);
	STDMETHOD(get_ErrorMsg)(/*[in]*/ long ErrorCode, /*[out, retval]*/ BSTR *pVal);
	STDMETHOD(get_LastErrorCode)(/*[out, retval]*/ long *pVal);
	STDMETHOD(get_Part)(/*[in]*/ long PartIndex, /*[out, retval]*/ long *pVal);
	STDMETHOD(put_Part)(/*[in]*/ long PartIndex, /*[in]*/ long newVal);
	STDMETHOD(get_Point)(/*[in]*/ long PointIndex, /*[out, retval]*/ IPoint * *pVal);
	STDMETHOD(put_Point)(/*[in]*/ long PointIndex, /*[in]*/ IPoint * newVal);
	STDMETHOD(get_ShapeType)(/*[out, retval]*/ ShpfileType *pVal);
	STDMETHOD(put_ShapeType)(/*[in]*/ ShpfileType newVal);
	STDMETHOD(get_NumParts)(/*[out, retval]*/ long *pVal);
	STDMETHOD(get_NumPoints)(/*[out, retval]*/ long *pVal);
	STDMETHOD(SerializeToString)(/*[out, retval]*/ BSTR * Serialized);
	STDMETHOD(CreateFromString)(/*[in]*/ BSTR Serialized, /*[out, retval]*/ VARIANT_BOOL * retval);
	STDMETHOD(PointInThisPoly)(/*[in]*/ IPoint * pt, /*[out, retval]*/ VARIANT_BOOL *retval);
	STDMETHOD(get_Centroid)(IPoint** pVal);
	STDMETHOD(get_Length)(double *pVal);
	STDMETHOD(get_Perimeter)(double *pVal);
	STDMETHOD(get_Area)(double *pVal);
	// OGRGeometry methods and properties (lsu 06-aug-2009)
	STDMETHOD(Relates)(IShape* Shape, tkSpatialRelation Relation, VARIANT_BOOL* retval);
	STDMETHOD(Clip)(IShape* Shape, tkClipOperation Operation, IShape** retval);
	STDMETHOD(Distance)(IShape* Shape, DOUBLE* retval);
	STDMETHOD(Buffer)(DOUBLE Distance, long nQuadSegments, IShape** retval);
	STDMETHOD(Contains)(IShape* Shape, VARIANT_BOOL* retval);
	STDMETHOD(Crosses)(IShape* Shape, VARIANT_BOOL* retval);
	STDMETHOD(Disjoint)(IShape* Shape, VARIANT_BOOL* retval);
	STDMETHOD(Equals)(IShape* Shape, VARIANT_BOOL* retval);
	STDMETHOD(Intersects)(IShape* Shape, VARIANT_BOOL* retval);
	STDMETHOD(Overlaps)(IShape* Shape, VARIANT_BOOL* retval);
	STDMETHOD(Touches)(IShape* Shape, VARIANT_BOOL* retval);
	STDMETHOD(Within)(IShape* Shape, VARIANT_BOOL* retval);
	STDMETHOD(Boundry)(IShape** retval);
	STDMETHOD(ConvexHull)(IShape** retval);
	STDMETHOD(get_IsValid)(VARIANT_BOOL* retval);
	STDMETHOD(get_XY)(long PointIndex, double* x, double* y, VARIANT_BOOL* retval);
	STDMETHOD(get_PartIsClockWise)(long PartIndex, VARIANT_BOOL* retval);
	STDMETHOD(ReversePointsOrder)(long PartIndex, VARIANT_BOOL* retval);
	STDMETHOD(GetIntersection)(IShape* Shape, VARIANT* Results, VARIANT_BOOL* retval);
	STDMETHOD(get_Center)(IPoint **pVal);
	STDMETHOD(get_EndOfPart)(long PartIndex, long* retval);	
	STDMETHOD(get_PartAsShape)(long PartIndex, IShape** retval);
	STDMETHOD(get_IsValidReason)(BSTR* retval);
	STDMETHOD(get_InteriorPoint)(IPoint** retval);
	STDMETHOD(Clone)(IShape** retval);
	STDMETHOD(Explode)(VARIANT* Results, VARIANT_BOOL* retval);
	STDMETHOD(put_XY)(LONG pointIndex, DOUBLE x, DOUBLE y, VARIANT_BOOL* retVal);
	STDMETHOD(ExportToBinary)(VARIANT* bytesArray, VARIANT_BOOL* retVal);
	STDMETHOD(ImportFromBinary)(VARIANT bytesArray, VARIANT_BOOL* retVal);
	STDMETHOD(FixUp)(IShape** retval);
	STDMETHOD(AddPoint)(double x, double y, long* pointIndex);
	
	bool CShape::ExplodeCore(std::vector<IShape*>& vShapes);
	CShapeWrapperCOM* CShape::InitComWrapper(CShapeWrapper* shpOld);
	CShapeWrapper* CShape::InitShapeWrapper(CShapeWrapperCOM* shpOld);

private:
	// members
	BSTR _key;
	long _lastErrorCode;
	ICallback * _globalCallback;
	CString _isValidReason;

	// either CShapeWrapper or CShapeWrapperCOM
	IShapeWrapper* _shp;

	// forces to use fast shape wrapper class to hold points information
	bool _useFastMode;							
	
	// functions
	void ErrorMessage(long ErrorCode);
	bool CShape::PointInThisPolyFast(IPoint * pt);
	bool CShape::PointInThisPolyRegular(IPoint * pt);
	
public:
	bool put_ShapeWrapper(CShapeWrapper* data);
	IShapeWrapper* get_ShapeWrapper();
	void CShape::put_fastMode(bool state);				// toggles the storing mode for the shape
	bool CShape::get_fastMode();
	double CShape::get_SegmentAngle( long segementIndex);
	void CShape::put_fastModeAdd(bool state);
	void CShape::get_LabelPosition(tkLabelPositioning method, double& x, double& y, double& rotation, tkLineLabelOrientation orientation);
};

OBJECT_ENTRY_AUTO(__uuidof(Shape), CShape)