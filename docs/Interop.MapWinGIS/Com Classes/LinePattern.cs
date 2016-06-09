﻿
#if nsp
namespace MapWinGIS
{
#endif
    using System;

    /// <summary>
    /// Provides means for defining custom pattern from lines and point symbols for rendering polyline layers.
    /// </summary>
    /// <remarks>The line pattern consists of line segments which can be representing by lines of various style, 
    /// width and color or by markers. Line segments are drawn one atop of the other in the sequence defined 
    /// in the line pattern.</remarks> \n\n
    /// Here is a diagram for the LinePattern class.
    /// \dot
    /// digraph pattern_diagram {
    /// nodesep = 0.3;
    /// ranksep = 0.3;
    /// splines = ortho;
    /// 
    /// node [shape= "polygon", peripheries = 3, fontname=Helvetica, fontsize=9, color = gray, style = filled, height = 0.2, width = 0.8];
    /// segm [ label="LineSegment" URL="\ref LineSegment"];
    /// 
    /// node [color = tan, peripheries = 1, height = 0.3, width = 1.0];
    /// ptrn [label="LinePattern" URL="\ref LinePattern"];
    /// 
    /// node [style = dashed, color = gray];
    /// sdo [ label="ShapeDrawingOptions" URL="\ref ShapeDrawingOptions"];
    /// 
    /// edge [ dir = "none", style = solid, fontname = "Arial", fontsize = 9, fontcolor = blue, color = "#606060", labeldistance = 0.6 ]
    /// sdo -> ptrn [ URL="\ref ShapeDrawingOptions.LinePattern", tooltip = "ShapeDrawingOptions.LinePattern", headlabel = "   1"];
    /// ptrn -> segm [ URL="\ref LinePattern.get_Line()", tooltip = "LinePattern.get_Line()", headlabel = "   n"];
    /// }
    /// \enddot
    /// <a href = "diagrams.html">Graph description</a>
    /// \new48 Added in version 4.8
    #if nsp
        #if upd
            public class LinePattern : MapWinGIS.ILinePattern
        #else        
            public class ILinePattern
        #endif
    #else
        public class LinePattern
    #endif
    {
        #region ILinePattern Members
        /// <summary>
        /// Adds a line segment to the pattern.
        /// </summary>
        /// <param name="Color">The color of the line.</param>
        /// <param name="Width">The width of the line.</param>
        /// <param name="style">The style of the line.</param>
        public void AddLine(uint Color, float Width, tkDashStyle style)
        {
            throw new NotImplementedException();
        }

        /// <summary>
        /// Adds a segment represented by point symbol (marker).
        /// </summary>
        /// <param name="Marker">The type of the marker.</param>
        /// <returns>Reference to the newly added segment or NULL reference on failure.</returns>
        public LineSegment AddMarker(tkDefaultPointSymbol Marker)
        {
            throw new NotImplementedException();
        }

        /// <summary>
        /// Removes all the line segments from the pattern.
        /// </summary>
        public void Clear()
        {
            throw new NotImplementedException();
        }

        /// <summary>
        /// Returns the number of all segments in the pattern.
        /// </summary>
        public int Count
        {
            get { throw new NotImplementedException(); }
        }

        /// <summary>
        /// Restores the state of the line segment from the string.
        /// </summary>
        /// <param name="newVal">A string generated by LinePattern.Serialize() method.</param>
        public void Deserialize(string newVal)
        {
            throw new NotImplementedException();
        }

        /// <summary>
        /// Draws a line pattern on the specified device context.
        /// </summary>
        /// <remarks>The method can be used to draw map legend.</remarks>
        /// <param name="hdc">The handle of the device context.</param>
        /// <param name="x">The x coordinate of the upper left corner of the drawing.</param>
        /// <param name="y">The y coordinate of the upper left corner of the drawing.</param>
        /// <param name="clipWidth">The width of the clipping rectangle.</param>
        /// <param name="clipHeight">The height of the clipping rectangle.</param>
        /// <param name="BackColor">The back color of the device context the drawing is performed at.
        /// The value should be specified to ensure correct blending when semi-transparent colors are used.</param>
        /// <returns>True on successful drawing and false on failure.</returns>
        public bool Draw(IntPtr hdc, float x, float y, int clipWidth, int clipHeight, uint BackColor)
        {
            throw new NotImplementedException();
        }

        /// <summary>
        /// Draws a line pattern on the specified device context.
        /// </summary>
        /// <remarks>The method can be used to draw map legend.</remarks>
        /// <param name="hdc">The handle of the device context.</param>
        /// <param name="x">The x coordinate of the upper left corner of the drawing.</param>
        /// <param name="y">The y coordinate of the upper left corner of the drawing.</param>
        /// <param name="clipWidth">The width of the clipping rectangle.</param>
        /// <param name="clipHeight">The height of the clipping rectangle.</param>
        /// <param name="BackColor">The back color of the device context the drawing is performed at.
        /// The value should be specified to ensure correct blending when semi-transparent colors are used.</param>
        /// <returns>True on successful drawing and false on failure.</returns>
        public bool DrawVB(int hdc, float x, float y, int clipWidth, int clipHeight, uint BackColor)
        {
            throw new NotImplementedException();
        }

        /// <summary>
        /// Gets or sets the global callback object which is used for passing to the client 
        /// the information about the progress of time consuming tasks and errors.
        /// </summary>
        /// <remarks>An instance of the class which implements ICallback interface should be passed.
        /// The class should be implemented by caller.</remarks>
        /// \deprecated v4.9.3 Use GlobalSettings.ApplicationCallback instead.
        public ICallback GlobalCallback
        {
            get { throw new NotImplementedException(); }
            set { throw new NotImplementedException(); }
        }

        /// <summary>
        /// Inserts line definition at the specified position of the pattern.
        /// </summary>
        /// <param name="Index">The index to insert the new line segment at.</param>
        /// <param name="Color">The color of the line.</param>
        /// <param name="Width">The width of the line.</param>
        /// <param name="style">The style of the line.</param>
        /// <returns>True on success and false otherwise.</returns>
        public bool InsertLine(int Index, uint Color, float Width, tkDashStyle style)
        {
            throw new NotImplementedException();
        }

        /// <summary>
        /// Insert marker definition on the pattern at the specified position. 
        /// </summary>
        /// <param name="Index">The index to insert the new segment at.</param>
        /// <param name="Marker">The type of marker.</param>
        /// <returns>True on success and false otherwise.</returns>
        public LineSegment InsertMarker(int Index, tkDefaultPointSymbol Marker)
        {
            throw new NotImplementedException();
        }

        /// <summary>
        /// Gets or sets a string value associated with the instance of the class. 
        /// It can store any information provided developer.
        /// </summary>
        public string Key
        {
            get { throw new NotImplementedException(); }
            set { throw new NotImplementedException(); }
        }

        /// <summary>
        /// Retrieves the numeric code of the last error that took place in the class.
        /// </summary>
        /// <remarks>The usage of this property clears the error code.</remarks>
        public int LastErrorCode
        {
            get { throw new NotImplementedException(); }
        }

        /// <summary>
        /// Removes a segment stored at the specified position of the pattern.
        /// </summary>
        /// <param name="Index">The position to remove the segment at.</param>
        /// <returns>True on success and false otherwise.</returns>
        public bool RemoveItem(int Index)
        {
            throw new NotImplementedException();
        }

        /// <summary>
        /// Saves the state of the object to the string.
        /// </summary>
        /// <returns>A string with serialized state.</returns>
        public string Serialize()
        {
            throw new NotImplementedException();
        }

        /// <summary>
        /// Gets or sets the transparency of the line pattern. The value ranges from 0(opaque) to 255(transparent).
        /// </summary>
        /// <remarks>The default value is 255. The setting affects the drawing of both lines and markers.</remarks>
        public byte Transparency
        {
            get { throw new NotImplementedException(); }
            set { throw new NotImplementedException(); }
        }

        /// <summary>
        /// Gets the text description of the specified error code.
        /// </summary>
        /// <param name="ErrorCode">The numeric error code retrieved by ShapeDrawingOptions.LastErrorCode property.</param>
        /// <returns>The description of the error.</returns>
        public string get_ErrorMsg(int ErrorCode)
        {
            throw new NotImplementedException();
        }

        /// <summary>
        /// Gets the reference to the line segment stored at the specified position in the pattern.
        /// </summary>
        /// <param name="Index">The index of the segment.</param>
        /// <returns>The reference to the line segment or NULL reference on failure.</returns>
        public LineSegment get_Line(int Index)
        {
            throw new NotImplementedException();
        }

        /// <summary>
        /// Changes line segment at the specified position to the new one. 
        /// </summary>
        /// <param name="Index">The index of segment.</param>
        /// <param name="retval">The reference to the new segment.</param>
        public void set_Line(int Index, LineSegment retval)
        {
            throw new NotImplementedException();
        }

        #endregion
    }
#if nsp
}
#endif

