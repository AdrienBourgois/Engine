#pragma once

///@cond DUPLICATE_MACRO
#ifdef ENGINECORE_EXPORTS
#define ENGINEDLL_API __declspec(dllexport)
#else
#define ENGINEDLL_API __declspec(dllimport)
#endif
///@endcond

namespace Core
{
	namespace CoreType
	{
		/**
		 * \brief RGBA Color class
		 * Colors components are stored with a range value of 0-1
		 */
		class ENGINEDLL_API Color
		{
		public:
			/**
			 * \brief Default constructor
			 */
			Color() = default;
			/**
			 * \brief Contructor for range value 0-1
			 * \param _r Red component
			 * \param _g Green component
			 * \param _b Blue component
			 * \param _a Alpha component (Default = 1.f / Visible)
			 */
			Color(float _r, float _g, float _b, float _a = 1.f);
			/**
			 * \brief Contructor for range value 0-255
			 * \param _r Red component
			 * \param _g Green component
			 * \param _b Blue component
			 * \param _a Alpha component (Default = 255 / Visible)
			 */
			Color(unsigned char _r, unsigned char _g, unsigned char _b, unsigned char _a = 255);
			/**
			 * \brief Default destructor
			 */
			~Color() = default;

			/**
			 * \brief Red component
			 */
			float r = 0.f;
			/**
			 * \brief Green component
			 */
			float g = 0.f;
			/**
			 * \brief Blue component
			 */
			float b = 0.f;
			/**
			 * \brief Alpha component
			 */
			float a = 0.f;

			/** @name Common Colors
			 *  Classics colors
			 *  @{
			 */

			/**
			 * \brief White (1, 1, 1, 1)
			 */
			static Color White;
			/**
			 * \brief Black (0, 0, 0, 1)
			 */
			static Color Black;
			/**
			 * \brief Red (1, 0, 0, 1)
			 */
			static Color Red;
			/**
			 * \brief Green (0, 1, 0, 1)
			 */
			static Color Green;
			/**
			 * \brief Blue (0, 0, 1, 1)
			 */
			static Color Blue;

			/** @} */

			/** @name Various Colors
			 *  Various colors (from http://avatar.se/molscript/doc/colour_names.html)
			 *  @{
			 */

			/**
			 * \brief Aliceblue (0.941176, 0.972549, 1)
			 */
			static Color Aliceblue;
			/**
			 * \brief Antiquewhite (0.980392, 0.921569, 0.843137)
			 */
			static Color Antiquewhite;
			/**
			 * \brief Aquamarine (0.498039, 1, 0.831373)
			 */
			static Color Aquamarine;
			/**
			 * \brief Azure (0.941176, 1, 1)
			 */
			static Color Azure;
			/**
			 * \brief Beige (0.960784, 0.960784, 0.862745)
			 */
			static Color Beige;
			/**
			 * \brief Bisque (1, 0.894118, 0.768627)
			 */
			static Color Bisque;
			/**
			 * \brief Blanchedalmond (1, 0.921569, 0.803922)
			 */
			static Color Blanchedalmond;
			/**
			 * \brief Blueviolet (0.541176, 0.168627, 0.886275)
			 */
			static Color Blueviolet;
			/**
			 * \brief Brown (0.647059, 0.164706, 0.164706)
			 */
			static Color Brown;
			/**
			 * \brief Burlywood (0.870588, 0.721569, 0.529412)
			 */
			static Color Burlywood;
			/**
			 * \brief Cadetblue (0.372549, 0.619608, 0.627451)
			 */
			static Color Cadetblue;
			/**
			 * \brief Chartreuse (0.498039, 1, 0)
			 */
			static Color Chartreuse;
			/**
			 * \brief Chocolate (0.823529, 0.411765, 0.117647)
			 */
			static Color Chocolate;
			/**
			 * \brief Coral (1, 0.498039, 0.313725)
			 */
			static Color Coral;
			/**
			 * \brief Cornflowerblue (0.392157, 0.584314, 0.929412)
			 */
			static Color Cornflowerblue;
			/**
			 * \brief Cornsilk (1, 0.972549, 0.862745)
			 */
			static Color Cornsilk;
			/**
			 * \brief Crimson (0.862745, 0.0784314, 0.235294)
			 */
			static Color Crimson;
			/**
			 * \brief Cyan (0, 1, 1)
			 */
			static Color Cyan;
			/**
			 * \brief Darkblue (0, 0, 0.545098)
			 */
			static Color Darkblue;
			/**
			 * \brief Darkcyan (0, 0.545098, 0.545098)
			 */
			static Color Darkcyan;
			/**
			 * \brief Darkgoldenrod (0.721569, 0.52549, 0.0431373)
			 */
			static Color Darkgoldenrod;
			/**
			 * \brief Darkgray (0.662745, 0.662745, 0.662745)
			 */
			static Color Darkgray;
			/**
			 * \brief Darkgreen (0, 0.392157, 0)
			 */
			static Color Darkgreen;
			/**
			 * \brief Darkgrey (0.662745, 0.662745, 0.662745)
			 */
			static Color Darkgrey;
			/**
			 * \brief Darkkhaki (0.741176, 0.717647, 0.419608)
			 */
			static Color Darkkhaki;
			/**
			 * \brief Darkmagenta (0.545098, 0, 0.545098)
			 */
			static Color Darkmagenta;
			/**
			 * \brief Darkolivegreen (0.333333, 0.419608, 0.184314)
			 */
			static Color Darkolivegreen;
			/**
			 * \brief Darkorange (1, 0.54902, 0)
			 */
			static Color Darkorange;
			/**
			 * \brief Darkorchid (0.6, 0.196078, 0.8)
			 */
			static Color Darkorchid;
			/**
			 * \brief Darkred (0.545098, 0, 0)
			 */
			static Color Darkred;
			/**
			 * \brief Darksalmon (0.913725, 0.588235, 0.478431)
			 */
			static Color Darksalmon;
			/**
			 * \brief Darkseagreen (0.560784, 0.737255, 0.560784)
			 */
			static Color Darkseagreen;
			/**
			 * \brief Darkslateblue (0.282353, 0.239216, 0.545098)
			 */
			static Color Darkslateblue;
			/**
			 * \brief Darkslategray (0.184314, 0.309804, 0.309804)
			 */
			static Color Darkslategray;
			/**
			 * \brief Darkslategrey (0.184314, 0.309804, 0.309804)
			 */
			static Color Darkslategrey;
			/**
			 * \brief Darkturquoise (0, 0.807843, 0.819608)
			 */
			static Color Darkturquoise;
			/**
			 * \brief Darkviolet (0.580392, 0, 0.827451)
			 */
			static Color Darkviolet;
			/**
			 * \brief Deeppink (1, 0.0784314, 0.576471)
			 */
			static Color Deeppink;
			/**
			 * \brief Deepskyblue (0, 0.74902, 1)
			 */
			static Color Deepskyblue;
			/**
			 * \brief Dimgray (0.411765, 0.411765, 0.411765)
			 */
			static Color Dimgray;
			/**
			 * \brief Dimgrey (0.411765, 0.411765, 0.411765)
			 */
			static Color Dimgrey;
			/**
			 * \brief Dodgerblue (0.117647, 0.564706, 1)
			 */
			static Color Dodgerblue;
			/**
			 * \brief Firebrick (0.698039, 0.133333, 0.133333)
			 */
			static Color Firebrick;
			/**
			 * \brief Floralwhite (1, 0.980392, 0.941176)
			 */
			static Color Floralwhite;
			/**
			 * \brief Forestgreen (0.133333, 0.545098, 0.133333)
			 */
			static Color Forestgreen;
			/**
			 * \brief Gainsboro (0.862745, 0.862745, 0.862745)
			 */
			static Color Gainsboro;
			/**
			 * \brief Ghostwhite (0.972549, 0.972549, 1)
			 */
			static Color Ghostwhite;
			/**
			 * \brief Gold (1, 0.843137, 0)
			 */
			static Color Gold;
			/**
			 * \brief Goldenrod (0.854902, 0.647059, 0.12549)
			 */
			static Color Goldenrod;
			/**
			 * \brief Gray (0.745098, 0.745098, 0.745098)
			 */
			static Color Gray;
			/**
			 * \brief Greenyellow (0.678431, 1, 0.184314)
			 */
			static Color Greenyellow;
			/**
			 * \brief Grey (0.745098, 0.745098, 0.745098)
			 */
			static Color Grey;
			/**
			 * \brief Honeydew (0.941176, 1, 0.941176)
			 */
			static Color Honeydew;
			/**
			 * \brief Hotpink (1, 0.411765, 0.705882)
			 */
			static Color Hotpink;
			/**
			 * \brief Indianred (0.803922, 0.360784, 0.360784)
			 */
			static Color Indianred;
			/**
			 * \brief Indigo (0.294118, 0, 0.509804)
			 */
			static Color Indigo;
			/**
			 * \brief Ivory (1, 1, 0.941176)
			 */
			static Color Ivory;
			/**
			 * \brief Khaki (0.941176, 0.901961, 0.54902)
			 */
			static Color Khaki;
			/**
			 * \brief Lavender (0.901961, 0.901961, 0.980392)
			 */
			static Color Lavender;
			/**
			 * \brief Lavenderblush (1, 0.941176, 0.960784)
			 */
			static Color Lavenderblush;
			/**
			 * \brief Lawngreen (0.486275, 0.988235, 0)
			 */
			static Color Lawngreen;
			/**
			 * \brief Lemonchiffon (1, 0.980392, 0.803922)
			 */
			static Color Lemonchiffon;
			/**
			 * \brief Lightblue (0.678431, 0.847059, 0.901961)
			 */
			static Color Lightblue;
			/**
			 * \brief Lightcoral (0.941176, 0.501961, 0.501961)
			 */
			static Color Lightcoral;
			/**
			 * \brief Lightcyan (0.878431, 1, 1)
			 */
			static Color Lightcyan;
			/**
			 * \brief Lightgoldenrod (0.933333, 0.866667, 0.509804)
			 */
			static Color Lightgoldenrod;
			/**
			 * \brief Lightgoldenrodyellow (0.980392, 0.980392, 0.823529)
			 */
			static Color Lightgoldenrodyellow;
			/**
			 * \brief Lightgray (0.827451, 0.827451, 0.827451)
			 */
			static Color Lightgray;
			/**
			 * \brief Lightgreen (0.564706, 0.933333, 0.564706)
			 */
			static Color Lightgreen;
			/**
			 * \brief Lightgrey (0.827451, 0.827451, 0.827451)
			 */
			static Color Lightgrey;
			/**
			 * \brief Lightpink (1, 0.713725, 0.756863)
			 */
			static Color Lightpink;
			/**
			 * \brief Lightsalmon (1, 0.627451, 0.478431)
			 */
			static Color Lightsalmon;
			/**
			 * \brief Lightseagreen (0.12549, 0.698039, 0.666667)
			 */
			static Color Lightseagreen;
			/**
			 * \brief Lightskyblue (0.529412, 0.807843, 0.980392)
			 */
			static Color Lightskyblue;
			/**
			 * \brief Lightslateblue (0.517647, 0.439216, 1)
			 */
			static Color Lightslateblue;
			/**
			 * \brief Lightslategray (0.466667, 0.533333, 0.6)
			 */
			static Color Lightslategray;
			/**
			 * \brief Lightslategrey (0.466667, 0.533333, 0.6)
			 */
			static Color Lightslategrey;
			/**
			 * \brief Lightsteelblue (0.690196, 0.768627, 0.870588)
			 */
			static Color Lightsteelblue;
			/**
			 * \brief Lightyellow (1, 1, 0.878431)
			 */
			static Color Lightyellow;
			/**
			 * \brief Limegreen (0.196078, 0.803922, 0.196078)
			 */
			static Color Limegreen;
			/**
			 * \brief Linen (0.980392, 0.941176, 0.901961)
			 */
			static Color Linen;
			/**
			 * \brief Magenta (1, 0, 1)
			 */
			static Color Magenta;
			/**
			 * \brief Maroon (0.690196, 0.188235, 0.376471)
			 */
			static Color Maroon;
			/**
			 * \brief Mediumaquamarine (0.4, 0.803922, 0.666667)
			 */
			static Color Mediumaquamarine;
			/**
			 * \brief Mediumblue (0, 0, 0.803922)
			 */
			static Color Mediumblue;
			/**
			 * \brief Mediumorchid (0.729412, 0.333333, 0.827451)
			 */
			static Color Mediumorchid;
			/**
			 * \brief Mediumpurple (0.576471, 0.439216, 0.858824)
			 */
			static Color Mediumpurple;
			/**
			 * \brief Mediumseagreen (0.235294, 0.701961, 0.443137)
			 */
			static Color Mediumseagreen;
			/**
			 * \brief Mediumslateblue (0.482353, 0.407843, 0.933333)
			 */
			static Color Mediumslateblue;
			/**
			 * \brief Mediumspringgreen (0, 0.980392, 0.603922)
			 */
			static Color Mediumspringgreen;
			/**
			 * \brief Mediumturquoise (0.282353, 0.819608, 0.8)
			 */
			static Color Mediumturquoise;
			/**
			 * \brief Mediumvioletred (0.780392, 0.0823529, 0.521569)
			 */
			static Color Mediumvioletred;
			/**
			 * \brief Midnightblue (0.0980392, 0.0980392, 0.439216)
			 */
			static Color Midnightblue;
			/**
			 * \brief Mintcream (0.960784, 1, 0.980392)
			 */
			static Color Mintcream;
			/**
			 * \brief Mistyrose (1, 0.894118, 0.882353)
			 */
			static Color Mistyrose;
			/**
			 * \brief Moccasin (1, 0.894118, 0.709804)
			 */
			static Color Moccasin;
			/**
			 * \brief Navajowhite (1, 0.870588, 0.678431)
			 */
			static Color Navajowhite;
			/**
			 * \brief Navy (0, 0, 0.501961)
			 */
			static Color Navy;
			/**
			 * \brief Navyblue (0, 0, 0.501961)
			 */
			static Color Navyblue;
			/**
			 * \brief Oldlace (0.992157, 0.960784, 0.901961)
			 */
			static Color Oldlace;
			/**
			 * \brief Olivedrab (0.419608, 0.556863, 0.137255)
			 */
			static Color Olivedrab;
			/**
			 * \brief Orange (1, 0.647059, 0)
			 */
			static Color Orange;
			/**
			 * \brief Orangered (1, 0.270588, 0)
			 */
			static Color Orangered;
			/**
			 * \brief Orchid (0.854902, 0.439216, 0.839216)
			 */
			static Color Orchid;
			/**
			 * \brief Palegoldenrod (0.933333, 0.909804, 0.666667)
			 */
			static Color Palegoldenrod;
			/**
			 * \brief Palegreen (0.596078, 0.984314, 0.596078)
			 */
			static Color Palegreen;
			/**
			 * \brief Paleturquoise (0.686275, 0.933333, 0.933333)
			 */
			static Color Paleturquoise;
			/**
			 * \brief Palevioletred (0.858824, 0.439216, 0.576471)
			 */
			static Color Palevioletred;
			/**
			 * \brief Papayawhip (1, 0.937255, 0.835294)
			 */
			static Color Papayawhip;
			/**
			 * \brief Peachpuff (1, 0.854902, 0.72549)
			 */
			static Color Peachpuff;
			/**
			 * \brief Peru (0.803922, 0.521569, 0.247059)
			 */
			static Color Peru;
			/**
			 * \brief Pink (1, 0.752941, 0.796078)
			 */
			static Color Pink;
			/**
			 * \brief Plum (0.866667, 0.627451, 0.866667)
			 */
			static Color Plum;
			/**
			 * \brief Powderblue (0.690196, 0.878431, 0.901961)
			 */
			static Color Powderblue;
			/**
			 * \brief Purple (0.627451, 0.12549, 0.941176)
			 */
			static Color Purple;
			/**
			 * \brief Rosybrown (0.737255, 0.560784, 0.560784)
			 */
			static Color Rosybrown;
			/**
			 * \brief Royalblue (0.254902, 0.411765, 0.882353)
			 */
			static Color Royalblue;
			/**
			 * \brief Saddlebrown (0.545098, 0.270588, 0.0745098)
			 */
			static Color Saddlebrown;
			/**
			 * \brief Salmon (0.980392, 0.501961, 0.447059)
			 */
			static Color Salmon;
			/**
			 * \brief Sandybrown (0.956863, 0.643137, 0.376471)
			 */
			static Color Sandybrown;
			/**
			 * \brief Seagreen (0.180392, 0.545098, 0.341176)
			 */
			static Color Seagreen;
			/**
			 * \brief Seashell (1, 0.960784, 0.933333)
			 */
			static Color Seashell;
			/**
			 * \brief Sgibeet (0.556863, 0.219608, 0.556863)
			 */
			static Color Sgibeet;
			/**
			 * \brief Sgibrightgray (0.772549, 0.756863, 0.666667)
			 */
			static Color Sgibrightgray;
			/**
			 * \brief Sgibrightgrey (0.772549, 0.756863, 0.666667)
			 */
			static Color Sgibrightgrey;
			/**
			 * \brief Sgichartreuse (0.443137, 0.776471, 0.443137)
			 */
			static Color Sgichartreuse;
			/**
			 * \brief Sgidarkgray (0.333333, 0.333333, 0.333333)
			 */
			static Color Sgidarkgray;
			/**
			 * \brief Sgidarkgrey (0.333333, 0.333333, 0.333333)
			 */
			static Color Sgidarkgrey;
			/**
			 * \brief Sgilightblue (0.490196, 0.619608, 0.752941)
			 */
			static Color Sgilightblue;
			/**
			 * \brief Sgilightgray (0.666667, 0.666667, 0.666667)
			 */
			static Color Sgilightgray;
			/**
			 * \brief Sgilightgrey (0.666667, 0.666667, 0.666667)
			 */
			static Color Sgilightgrey;
			/**
			 * \brief Sgimediumgray (0.517647, 0.517647, 0.517647)
			 */
			static Color Sgimediumgray;
			/**
			 * \brief Sgimediumgrey (0.517647, 0.517647, 0.517647)
			 */
			static Color Sgimediumgrey;
			/**
			 * \brief Sgiolivedrab (0.556863, 0.556863, 0.219608)
			 */
			static Color Sgiolivedrab;
			/**
			 * \brief Sgisalmon (0.776471, 0.443137, 0.443137)
			 */
			static Color Sgisalmon;
			/**
			 * \brief Sgislateblue (0.443137, 0.443137, 0.776471)
			 */
			static Color Sgislateblue;
			/**
			 * \brief Sgiteal (0.219608, 0.556863, 0.556863)
			 */
			static Color Sgiteal;
			/**
			 * \brief Sgiverydarkgray (0.156863, 0.156863, 0.156863)
			 */
			static Color Sgiverydarkgray;
			/**
			 * \brief Sgiverydarkgrey (0.156863, 0.156863, 0.156863)
			 */
			static Color Sgiverydarkgrey;
			/**
			 * \brief Sgiverylightgray (0.839216, 0.839216, 0.839216)
			 */
			static Color Sgiverylightgray;
			/**
			 * \brief Sgiverylightgrey (0.839216, 0.839216, 0.839216)
			 */
			static Color Sgiverylightgrey;
			/**
			 * \brief Sienna (0.627451, 0.321569, 0.176471)
			 */
			static Color Sienna;
			/**
			 * \brief Skyblue (0.529412, 0.807843, 0.921569)
			 */
			static Color Skyblue;
			/**
			 * \brief Slateblue (0.415686, 0.352941, 0.803922)
			 */
			static Color Slateblue;
			/**
			 * \brief Slategray (0.439216, 0.501961, 0.564706)
			 */
			static Color Slategray;
			/**
			 * \brief Slategrey (0.439216, 0.501961, 0.564706)
			 */
			static Color Slategrey;
			/**
			 * \brief Snow (1, 0.980392, 0.980392)
			 */
			static Color Snow;
			/**
			 * \brief Springgreen (0, 1, 0.498039)
			 */
			static Color Springgreen;
			/**
			 * \brief Steelblue (0.27451, 0.509804, 0.705882)
			 */
			static Color Steelblue;
			/**
			 * \brief Tan (0.823529, 0.705882, 0.54902)
			 */
			static Color Tan;
			/**
			 * \brief Thistle (0.847059, 0.74902, 0.847059)
			 */
			static Color Thistle;
			/**
			 * \brief Tomato (1, 0.388235, 0.278431)
			 */
			static Color Tomato;
			/**
			 * \brief Turquoise (0.25098, 0.878431, 0.815686)
			 */
			static Color Turquoise;
			/**
			 * \brief Violet (0.933333, 0.509804, 0.933333)
			 */
			static Color Violet;
			/**
			 * \brief Violetred (0.815686, 0.12549, 0.564706)
			 */
			static Color Violetred;
			/**
			 * \brief Wheat (0.960784, 0.870588, 0.701961)
			 */
			static Color Wheat;
			/**
			 * \brief Whitesmoke (0.960784, 0.960784, 0.960784)
			 */
			static Color Whitesmoke;
			/**
			 * \brief Yellow (1, 1, 0)
			 */
			static Color Yellow;
			/**
			 * \brief Yellowgreen (0.603922, 0.803922, 0.196078)
			 */
			static Color Yellowgreen;

			/** @} */
		};

		/**
		 * \brief Fill an array with color components
		 * \warning Array must be a 4 float array
		 * \param _array Array to populate
		 * \param _color Color to use
		 * \return Pointer to array
		 */
		const float* FillArrayColor(float* _array, Color _color);
	}
}