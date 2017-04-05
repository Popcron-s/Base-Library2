#pragma once

namespace _GRAPH{
	enum TYPE{
		NONE = 0,
		STOP,
		PAUSE,
		PLAY_ONCE,
		PLAT_LOOP
	};
	enum INTERPOLATION{
		POINT,
		CLIFF,
		LINEAR,
		SQUARED,
		INVSQURED
	};
};

namespace _OBJECT{
	enum TYPE{
		NONE = 0,
		Root,
		Material,
		Mesh,
		IndexedMesh,
		Collider,
		Sound,
		Animation
	};
};

namespace _COLLISION{
	enum TYPE{
		Ignore,
		Overlap,
		Block
	};
}

namespace _PLATFORM{
	enum TYPE{
		Win32,
		Win64,
		Android,
		iOS
	};
}

namespace _INTERFACE{
	namespace GRAPHIC{
		enum TYPE{
			OpenGL,
			DX9,
			DX11
		};
	}

	namespace AUDIO{
		enum TYPE{

		};
	}
}