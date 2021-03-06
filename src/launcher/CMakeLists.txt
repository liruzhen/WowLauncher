
add_definitions(-DUNICODE -D_UNICODE)

set (BASE_SOURCES 
	Manifest.cpp
	Main.hpp 			Main.cpp
	MainFrame.hpp 		MainFrame.cpp
	Process.hpp 		Process.cpp
	Realm.hpp 			Realm.cpp
	RealmList.hpp 		RealmList.cpp
	WindowsError.hpp 	WindowsError.cpp
	Application.hpp 	Application.cpp
)

set (GUI_SOURCES
	gui/MessageBox.hpp 	gui/MessageBox.cpp
	gui/Frame.hpp 		gui/Frame.cpp
	gui/Dialog.hpp 		gui/Dialog.cpp
	gui/Widget.hpp 		gui/Widget.cpp
	gui/Label.hpp 		gui/Label.cpp
	gui/ComboBox.hpp 	gui/ComboBox.cpp
	gui/TextBox.hpp 	gui/TextBox.cpp
	gui/Button.hpp 		gui/Button.cpp
	gui/Image.hpp 		gui/Image.cpp
	gui/ListView.hpp 	gui/ListView.cpp
	gui/MenuBase.hpp 	gui/MenuBase.cpp
	gui/MenuBar.hpp 	gui/MenuBar.cpp
	gui/MenuHandler.hpp gui/MenuHandler.cpp
	gui/Menu.hpp 		gui/Menu.cpp
	gui/MenuItem.hpp 	gui/MenuItem.cpp
)

source_group("\\" FILES ${BASE_SOURCES})
source_group("\\gui" FILES ${GUI_SOURCES})

add_executable(WowLauncher WIN32 ${BASE_SOURCES} ${GUI_SOURCES})

target_link_libraries(WowLauncher comctl32)