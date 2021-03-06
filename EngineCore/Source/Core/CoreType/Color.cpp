#include "Color.h"

Core::CoreType::Color::Color(float _r, float _g, float _b, float _a): r(_r), g(_g), b(_b), a(_a)
{}

Core::CoreType::Color::Color(unsigned char _r, unsigned char _g, unsigned char _b, unsigned char _a)
{
	r = _r / 255.f;
	g = _g / 255.f;
	b = _b / 255.f;
	a = _a / 255.f;
}

const float* Core::CoreType::Color::FillArrayColor(float* _array, const Color _color)
{
	_array[0] = _color.r;
	_array[1] = _color.g;
	_array[2] = _color.b;
	_array[3] = _color.a;

	return _array;
}

///@cond IGNORE_COLORS_IMPLEMENTATION

Core::CoreType::Color Core::CoreType::Color::White = Color(1.f, 1.f, 1.f, 1.f);
Core::CoreType::Color Core::CoreType::Color::Black = Color(0.f, 0.f, 0.f, 1.f);
Core::CoreType::Color Core::CoreType::Color::Red   = Color(1.f, 0.f, 0.f, 1.f);
Core::CoreType::Color Core::CoreType::Color::Green = Color(0.f, 1.f, 0.f, 1.f);
Core::CoreType::Color Core::CoreType::Color::Blue  = Color(0.f, 0.f, 1.f, 1.f);

Core::CoreType::Color Core::CoreType::Color::Aliceblue            = Color(0.941176f, 0.972549f,  1.f,        1.f);
Core::CoreType::Color Core::CoreType::Color::Antiquewhite         = Color(0.980392f, 0.921569f,  0.843137f,  1.f);
Core::CoreType::Color Core::CoreType::Color::Aquamarine           = Color(0.498039f, 1.f,        0.831373f,  1.f);
Core::CoreType::Color Core::CoreType::Color::Azure                = Color(0.941176f, 1.f,        1.f,        1.f);
Core::CoreType::Color Core::CoreType::Color::Beige                = Color(0.960784f, 0.960784f,  0.862745f,  1.f);
Core::CoreType::Color Core::CoreType::Color::Bisque               = Color(1.f      , 0.894118f,  0.768627f,  1.f);
Core::CoreType::Color Core::CoreType::Color::Blanchedalmond       = Color(1.f      , 0.921569f,  0.803922f,  1.f);
Core::CoreType::Color Core::CoreType::Color::Blueviolet           = Color(0.541176f, 0.168627f,  0.886275f,  1.f);
Core::CoreType::Color Core::CoreType::Color::Brown                = Color(0.647059f, 0.164706f,  0.164706f,  1.f);
Core::CoreType::Color Core::CoreType::Color::Burlywood            = Color(0.870588f, 0.721569f,  0.529412f,  1.f);
Core::CoreType::Color Core::CoreType::Color::Cadetblue            = Color(0.372549f, 0.619608f,  0.627451f,  1.f);
Core::CoreType::Color Core::CoreType::Color::Chartreuse           = Color(0.498039f, 1.f,        0.f,        1.f);
Core::CoreType::Color Core::CoreType::Color::Chocolate            = Color(0.823529f, 0.411765f,  0.117647f,  1.f);
Core::CoreType::Color Core::CoreType::Color::Coral                = Color(1.f      , 0.498039f,  0.313725f,  1.f);
Core::CoreType::Color Core::CoreType::Color::Cornflowerblue       = Color(0.392157f, 0.584314f,  0.929412f,  1.f);
Core::CoreType::Color Core::CoreType::Color::Cornsilk             = Color(1.f      , 0.972549f,  0.862745f,  1.f);
Core::CoreType::Color Core::CoreType::Color::Crimson              = Color(0.862745f, 0.0784314f, 0.235294f,  1.f);
Core::CoreType::Color Core::CoreType::Color::Cyan                 = Color(0.f      , 1.f,        1.f,        1.f);
Core::CoreType::Color Core::CoreType::Color::Darkblue             = Color(0.f      , 0.f,        0.545098f,  1.f);
Core::CoreType::Color Core::CoreType::Color::Darkcyan             = Color(0.f      , 0.545098f,  0.545098f,  1.f);
Core::CoreType::Color Core::CoreType::Color::Darkgoldenrod        = Color(0.721569f, 0.52549f,   0.0431373f, 1.f);
Core::CoreType::Color Core::CoreType::Color::Darkgray             = Color(0.662745f, 0.662745f,  0.662745f,  1.f);
Core::CoreType::Color Core::CoreType::Color::Darkgreen            = Color(0.f      , 0.392157f,  0.f,        1.f);
Core::CoreType::Color Core::CoreType::Color::Darkgrey             = Color(0.662745f, 0.662745f,  0.662745f,  1.f);
Core::CoreType::Color Core::CoreType::Color::Darkkhaki            = Color(0.741176f, 0.717647f,  0.419608f,  1.f);
Core::CoreType::Color Core::CoreType::Color::Darkmagenta          = Color(0.545098f, 0.f,        0.545098f,  1.f);
Core::CoreType::Color Core::CoreType::Color::Darkolivegreen       = Color(0.333333f, 0.419608f,  0.184314f,  1.f);
Core::CoreType::Color Core::CoreType::Color::Darkorange           = Color(1.f      , 0.54902f,   0.f,        1.f);
Core::CoreType::Color Core::CoreType::Color::Darkorchid           = Color(0.6f     , 0.196078f,  0.8f,       1.f);
Core::CoreType::Color Core::CoreType::Color::Darkred              = Color(0.545098f, 0.f,        0.f,        1.f);
Core::CoreType::Color Core::CoreType::Color::Darksalmon           = Color(0.913725f, 0.588235f,  0.478431f,  1.f);
Core::CoreType::Color Core::CoreType::Color::Darkseagreen         = Color(0.560784f, 0.737255f,  0.560784f,  1.f);
Core::CoreType::Color Core::CoreType::Color::Darkslateblue        = Color(0.282353f, 0.239216f,  0.545098f,  1.f);
Core::CoreType::Color Core::CoreType::Color::Darkslategray        = Color(0.184314f, 0.309804f,  0.309804f,  1.f);
Core::CoreType::Color Core::CoreType::Color::Darkslategrey        = Color(0.184314f, 0.309804f,  0.309804f,  1.f);
Core::CoreType::Color Core::CoreType::Color::Darkturquoise        = Color(0.f      , 0.807843f,  0.819608f,  1.f);
Core::CoreType::Color Core::CoreType::Color::Darkviolet           = Color(0.580392f, 0.f,        0.827451f,  1.f);
Core::CoreType::Color Core::CoreType::Color::Deeppink             = Color(1.f      , 0.0784314f, 0.576471f,  1.f);
Core::CoreType::Color Core::CoreType::Color::Deepskyblue          = Color(0.f      , 0.74902f,   1.f,        1.f);
Core::CoreType::Color Core::CoreType::Color::Dimgray              = Color(0.411765f, 0.411765f,  0.411765f,  1.f);
Core::CoreType::Color Core::CoreType::Color::Dimgrey              = Color(0.411765f, 0.411765f,  0.411765f,  1.f);
Core::CoreType::Color Core::CoreType::Color::Dodgerblue           = Color(0.117647f, 0.564706f,  1.f,        1.f);
Core::CoreType::Color Core::CoreType::Color::Firebrick            = Color(0.698039f, 0.133333f,  0.133333f,  1.f);
Core::CoreType::Color Core::CoreType::Color::Floralwhite          = Color(1.f      , 0.980392f,  0.941176f,  1.f);
Core::CoreType::Color Core::CoreType::Color::Forestgreen          = Color(0.133333f, 0.545098f,  0.133333f,  1.f);
Core::CoreType::Color Core::CoreType::Color::Gainsboro            = Color(0.862745f, 0.862745f,  0.862745f,  1.f);
Core::CoreType::Color Core::CoreType::Color::Ghostwhite           = Color(0.972549f, 0.972549f,  1.f,        1.f);
Core::CoreType::Color Core::CoreType::Color::Gold                 = Color(1.f      , 0.843137f,  0.f,        1.f);
Core::CoreType::Color Core::CoreType::Color::Goldenrod            = Color(0.854902f, 0.647059f,  0.12549f,   1.f);
Core::CoreType::Color Core::CoreType::Color::Gray                 = Color(0.745098f, 0.745098f,  0.745098f,  1.f);
Core::CoreType::Color Core::CoreType::Color::Greenyellow          = Color(0.678431f, 1.f,        0.184314f,  1.f);
Core::CoreType::Color Core::CoreType::Color::Grey                 = Color(0.745098f, 0.745098f,  0.745098f,  1.f);
Core::CoreType::Color Core::CoreType::Color::Honeydew             = Color(0.941176f, 1.f,        0.941176f,  1.f);
Core::CoreType::Color Core::CoreType::Color::Hotpink              = Color(1.f      , 0.411765f,  0.705882f,  1.f);
Core::CoreType::Color Core::CoreType::Color::Indianred            = Color(0.803922f, 0.360784f,  0.360784f,  1.f);
Core::CoreType::Color Core::CoreType::Color::Indigo               = Color(0.294118f, 0.f,        0.509804f,  1.f);
Core::CoreType::Color Core::CoreType::Color::Ivory                = Color(1.f      , 1.f,        0.941176f,  1.f);
Core::CoreType::Color Core::CoreType::Color::Khaki                = Color(0.941176f, 0.901961f,  0.54902f,   1.f);
Core::CoreType::Color Core::CoreType::Color::Lavender             = Color(0.901961f, 0.901961f,  0.980392f,  1.f);
Core::CoreType::Color Core::CoreType::Color::Lavenderblush        = Color(1.f      , 0.941176f,  0.960784f,  1.f);
Core::CoreType::Color Core::CoreType::Color::Lawngreen            = Color(0.486275f, 0.988235f,  0.f,        1.f);
Core::CoreType::Color Core::CoreType::Color::Lemonchiffon         = Color(1.f      , 0.980392f,  0.803922f,  1.f);
Core::CoreType::Color Core::CoreType::Color::Lightblue            = Color(0.678431f, 0.847059f,  0.901961f,  1.f);
Core::CoreType::Color Core::CoreType::Color::Lightcoral           = Color(0.941176f, 0.501961f,  0.501961f,  1.f);
Core::CoreType::Color Core::CoreType::Color::Lightcyan            = Color(0.878431f, 1.f,        1.f,        1.f);
Core::CoreType::Color Core::CoreType::Color::Lightgoldenrod       = Color(0.933333f, 0.866667f,  0.509804f,  1.f);
Core::CoreType::Color Core::CoreType::Color::Lightgoldenrodyellow = Color(0.980392f, 0.980392f,  0.823529f,  1.f);
Core::CoreType::Color Core::CoreType::Color::Lightgray            = Color(0.827451f, 0.827451f,  0.827451f,  1.f);
Core::CoreType::Color Core::CoreType::Color::Lightgreen           = Color(0.564706f, 0.933333f,  0.564706f,  1.f);
Core::CoreType::Color Core::CoreType::Color::Lightgrey            = Color(0.827451f, 0.827451f,  0.827451f,  1.f);
Core::CoreType::Color Core::CoreType::Color::Lightpink            = Color(1.f      , 0.713725f,  0.756863f,  1.f);
Core::CoreType::Color Core::CoreType::Color::Lightsalmon          = Color(1.f      , 0.627451f,  0.478431f,  1.f);
Core::CoreType::Color Core::CoreType::Color::Lightseagreen        = Color(0.12549f , 0.698039f,  0.666667f,  1.f);
Core::CoreType::Color Core::CoreType::Color::Lightskyblue         = Color(0.529412f, 0.807843f,  0.980392f,  1.f);
Core::CoreType::Color Core::CoreType::Color::Lightslateblue       = Color(0.517647f, 0.439216f,  1.f,        1.f);
Core::CoreType::Color Core::CoreType::Color::Lightslategray       = Color(0.466667f, 0.533333f,  0.6f,       1.f);
Core::CoreType::Color Core::CoreType::Color::Lightslategrey       = Color(0.466667f, 0.533333f,  0.6f,       1.f);
Core::CoreType::Color Core::CoreType::Color::Lightsteelblue       = Color(0.690196f, 0.768627f,  0.870588f,  1.f);
Core::CoreType::Color Core::CoreType::Color::Lightyellow          = Color(1.f      , 1.f,        0.878431f,  1.f);
Core::CoreType::Color Core::CoreType::Color::Limegreen            = Color(0.196078f, 0.803922f,  0.196078f,  1.f);
Core::CoreType::Color Core::CoreType::Color::Linen                = Color(0.980392f, 0.941176f,  0.901961f,  1.f);
Core::CoreType::Color Core::CoreType::Color::Magenta              = Color(1.f      , 0.f,        1.f,        1.f);
Core::CoreType::Color Core::CoreType::Color::Maroon               = Color(0.690196f, 0.188235f,  0.376471f,  1.f);
Core::CoreType::Color Core::CoreType::Color::Mediumaquamarine     = Color(0.4f     , 0.803922f,  0.666667f,  1.f);
Core::CoreType::Color Core::CoreType::Color::Mediumblue           = Color(0.f      , 0.f,        0.803922f,  1.f);
Core::CoreType::Color Core::CoreType::Color::Mediumorchid         = Color(0.729412f, 0.333333f,  0.827451f,  1.f);
Core::CoreType::Color Core::CoreType::Color::Mediumpurple         = Color(0.576471f, 0.439216f,  0.858824f,  1.f);
Core::CoreType::Color Core::CoreType::Color::Mediumseagreen       = Color(0.235294f, 0.701961f,  0.443137f,  1.f);
Core::CoreType::Color Core::CoreType::Color::Mediumslateblue      = Color(0.482353f, 0.407843f,  0.933333f,  1.f);
Core::CoreType::Color Core::CoreType::Color::Mediumspringgreen    = Color(0.f      , 0.980392f,  0.603922f,  1.f);
Core::CoreType::Color Core::CoreType::Color::Mediumturquoise      = Color(0.282353f, 0.819608f,  0.8f,       1.f);
Core::CoreType::Color Core::CoreType::Color::Mediumvioletred      = Color(0.780392f, 0.0823529f, 0.521569f,  1.f);
Core::CoreType::Color Core::CoreType::Color::Midnightblue         = Color(0.098039f, 0.0980392f, 0.439216f,  1.f);
Core::CoreType::Color Core::CoreType::Color::Mintcream            = Color(0.960784f, 1.f,        0.980392f,  1.f);
Core::CoreType::Color Core::CoreType::Color::Mistyrose            = Color(1.f      , 0.894118f,  0.882353f,  1.f);
Core::CoreType::Color Core::CoreType::Color::Moccasin             = Color(1.f      , 0.894118f,  0.709804f,  1.f);
Core::CoreType::Color Core::CoreType::Color::Navajowhite          = Color(1.f      , 0.870588f,  0.678431f,  1.f);
Core::CoreType::Color Core::CoreType::Color::Navy                 = Color(0.f      , 0.f,        0.501961f,  1.f);
Core::CoreType::Color Core::CoreType::Color::Navyblue             = Color(0.f      , 0.f,        0.501961f,  1.f);
Core::CoreType::Color Core::CoreType::Color::Oldlace              = Color(0.992157f, 0.960784f,  0.901961f,  1.f);
Core::CoreType::Color Core::CoreType::Color::Olivedrab            = Color(0.419608f, 0.556863f,  0.137255f,  1.f);
Core::CoreType::Color Core::CoreType::Color::Orange               = Color(1.f      , 0.647059f,  0.f,        1.f);
Core::CoreType::Color Core::CoreType::Color::Orangered            = Color(1.f      , 0.270588f,  0.f,        1.f);
Core::CoreType::Color Core::CoreType::Color::Orchid               = Color(0.854902f, 0.439216f,  0.839216f,  1.f);
Core::CoreType::Color Core::CoreType::Color::Palegoldenrod        = Color(0.933333f, 0.909804f,  0.666667f,  1.f);
Core::CoreType::Color Core::CoreType::Color::Palegreen            = Color(0.596078f, 0.984314f,  0.596078f,  1.f);
Core::CoreType::Color Core::CoreType::Color::Paleturquoise        = Color(0.686275f, 0.933333f,  0.933333f,  1.f);
Core::CoreType::Color Core::CoreType::Color::Palevioletred        = Color(0.858824f, 0.439216f,  0.576471f,  1.f);
Core::CoreType::Color Core::CoreType::Color::Papayawhip           = Color(1.f      , 0.937255f,  0.835294f,  1.f);
Core::CoreType::Color Core::CoreType::Color::Peachpuff            = Color(1.f      , 0.854902f,  0.72549f,   1.f);
Core::CoreType::Color Core::CoreType::Color::Peru                 = Color(0.803922f, 0.521569f,  0.247059f,  1.f);
Core::CoreType::Color Core::CoreType::Color::Pink                 = Color(1.f      , 0.752941f,  0.796078f,  1.f);
Core::CoreType::Color Core::CoreType::Color::Plum                 = Color(0.866667f, 0.627451f,  0.866667f,  1.f);
Core::CoreType::Color Core::CoreType::Color::Powderblue           = Color(0.690196f, 0.878431f,  0.901961f,  1.f);
Core::CoreType::Color Core::CoreType::Color::Purple               = Color(0.627451f, 0.12549f,   0.941176f,  1.f);
Core::CoreType::Color Core::CoreType::Color::Rosybrown            = Color(0.737255f, 0.560784f,  0.560784f,  1.f);
Core::CoreType::Color Core::CoreType::Color::Royalblue            = Color(0.254902f, 0.411765f,  0.882353f,  1.f);
Core::CoreType::Color Core::CoreType::Color::Saddlebrown          = Color(0.545098f, 0.270588f,  0.0745098f, 1.f);
Core::CoreType::Color Core::CoreType::Color::Salmon               = Color(0.980392f, 0.501961f,  0.447059f,  1.f);
Core::CoreType::Color Core::CoreType::Color::Sandybrown           = Color(0.956863f, 0.643137f,  0.376471f,  1.f);
Core::CoreType::Color Core::CoreType::Color::Seagreen             = Color(0.180392f, 0.545098f,  0.341176f,  1.f);
Core::CoreType::Color Core::CoreType::Color::Seashell             = Color(1.f      , 0.960784f,  0.933333f,  1.f);
Core::CoreType::Color Core::CoreType::Color::Sgibeet              = Color(0.556863f, 0.219608f,  0.556863f,  1.f);
Core::CoreType::Color Core::CoreType::Color::Sgibrightgray        = Color(0.772549f, 0.756863f,  0.666667f,  1.f);
Core::CoreType::Color Core::CoreType::Color::Sgibrightgrey        = Color(0.772549f, 0.756863f,  0.666667f,  1.f);
Core::CoreType::Color Core::CoreType::Color::Sgichartreuse        = Color(0.443137f, 0.776471f,  0.443137f,  1.f);
Core::CoreType::Color Core::CoreType::Color::Sgidarkgray          = Color(0.333333f, 0.333333f,  0.333333f,  1.f);
Core::CoreType::Color Core::CoreType::Color::Sgidarkgrey          = Color(0.333333f, 0.333333f,  0.333333f,  1.f);
Core::CoreType::Color Core::CoreType::Color::Sgilightblue         = Color(0.490196f, 0.619608f,  0.752941f,  1.f);
Core::CoreType::Color Core::CoreType::Color::Sgilightgray         = Color(0.666667f, 0.666667f,  0.666667f,  1.f);
Core::CoreType::Color Core::CoreType::Color::Sgilightgrey         = Color(0.666667f, 0.666667f,  0.666667f,  1.f);
Core::CoreType::Color Core::CoreType::Color::Sgimediumgray        = Color(0.517647f, 0.517647f,  0.517647f,  1.f);
Core::CoreType::Color Core::CoreType::Color::Sgimediumgrey        = Color(0.517647f, 0.517647f,  0.517647f,  1.f);
Core::CoreType::Color Core::CoreType::Color::Sgiolivedrab         = Color(0.556863f, 0.556863f,  0.219608f,  1.f);
Core::CoreType::Color Core::CoreType::Color::Sgisalmon            = Color(0.776471f, 0.443137f,  0.443137f,  1.f);
Core::CoreType::Color Core::CoreType::Color::Sgislateblue         = Color(0.443137f, 0.443137f,  0.776471f,  1.f);
Core::CoreType::Color Core::CoreType::Color::Sgiteal              = Color(0.219608f, 0.556863f,  0.556863f,  1.f);
Core::CoreType::Color Core::CoreType::Color::Sgiverydarkgray      = Color(0.156863f, 0.156863f,  0.156863f,  1.f);
Core::CoreType::Color Core::CoreType::Color::Sgiverydarkgrey      = Color(0.156863f, 0.156863f,  0.156863f,  1.f);
Core::CoreType::Color Core::CoreType::Color::Sgiverylightgray     = Color(0.839216f, 0.839216f,  0.839216f,  1.f);
Core::CoreType::Color Core::CoreType::Color::Sgiverylightgrey     = Color(0.839216f, 0.839216f,  0.839216f,  1.f);
Core::CoreType::Color Core::CoreType::Color::Sienna               = Color(0.627451f, 0.321569f,  0.176471f,  1.f);
Core::CoreType::Color Core::CoreType::Color::Skyblue              = Color(0.529412f, 0.807843f,  0.921569f,  1.f);
Core::CoreType::Color Core::CoreType::Color::Slateblue            = Color(0.415686f, 0.352941f,  0.803922f,  1.f);
Core::CoreType::Color Core::CoreType::Color::Slategray            = Color(0.439216f, 0.501961f,  0.564706f,  1.f);
Core::CoreType::Color Core::CoreType::Color::Slategrey            = Color(0.439216f, 0.501961f,  0.564706f,  1.f);
Core::CoreType::Color Core::CoreType::Color::Snow                 = Color(1.f      , 0.980392f,  0.980392f,  1.f);
Core::CoreType::Color Core::CoreType::Color::Springgreen          = Color(0.f      , 1.f,        0.498039f,  1.f);
Core::CoreType::Color Core::CoreType::Color::Steelblue            = Color(0.27451f , 0.509804f,  0.705882f,  1.f);
Core::CoreType::Color Core::CoreType::Color::Tan                  = Color(0.823529f, 0.705882f,  0.54902f,   1.f);
Core::CoreType::Color Core::CoreType::Color::Thistle              = Color(0.847059f, 0.74902f,   0.847059f,  1.f);
Core::CoreType::Color Core::CoreType::Color::Tomato               = Color(1.f      , 0.388235f,  0.278431f,  1.f);
Core::CoreType::Color Core::CoreType::Color::Turquoise            = Color(0.25098f , 0.878431f,  0.815686f,  1.f);
Core::CoreType::Color Core::CoreType::Color::Violet               = Color(0.933333f, 0.509804f,  0.933333f,  1.f);
Core::CoreType::Color Core::CoreType::Color::Violetred            = Color(0.815686f, 0.12549f,   0.564706f,  1.f);
Core::CoreType::Color Core::CoreType::Color::Wheat                = Color(0.960784f, 0.870588f,  0.701961f,  1.f);
Core::CoreType::Color Core::CoreType::Color::Whitesmoke           = Color(0.960784f, 0.960784f,  0.960784f,  1.f);
Core::CoreType::Color Core::CoreType::Color::Yellow               = Color(1.f      , 1.f,        0.f,        1.f);
Core::CoreType::Color Core::CoreType::Color::Yellowgreen          = Color(0.603922f, 0.803922f,  0.196078f,  1.f);

///@endcond