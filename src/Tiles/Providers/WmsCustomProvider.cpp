/**************************************************************************************
 * Project: MapWindow Open Source (MapWinGis ActiveX control) 
 **************************************************************************************
 * The contents of this file are subject to the Mozilla Public License Version 1.1
 * (the "License"); you may not use this file except in compliance with 
 * the License. You may obtain a copy of the License at http://www.mozilla.org/mpl/ 
 * See the License for the specific language governing rights and limitations
 * under the License.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS
 * OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL
 * THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
 * DEALINGS IN THE SOFTWARE.
 ************************************************************************************** 
 * Contributor(s): 
 * (Open source contributors should list themselves and their modifications here). */
  
#include "stdafx.h"
#include "WmsCustomProvider.h"

// ******************************************************
//    MakeTileImageUrl()
// ******************************************************
CString WmsCustomProvider::MakeTileImageUrl(CPoint &pos, int zoom)
{
	CString s = _urlFormat;

	s += "?request=GetMap&service=WMS";  
	s += "&layers=" + _layers;

	s += "&";
	CString temp;
	temp.Format("&srs=EPSG:%d", get_CustomProjection()->get_Epsg());
	s += temp;

	s += "&bbox=" + GetBoundingBox(pos, zoom);
	s += "&format=" + _format;
	s += "&width=256";
	s += "&height=256";
	s += "&version=1.1.1";
	s += "&styles=";

	return s;
}




