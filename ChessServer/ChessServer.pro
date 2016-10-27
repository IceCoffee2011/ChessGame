TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

QMAKE_CXXFLAGS += -std=c++11

INCLUDEPATH += D:/local/libevent/include
INCLUDEPATH += D:/local/mysql/include D:/local/mysql/include/mysql
QMAKE_LFLAGS += -LD:/local/libevent/ -LD:/local/mysql

LIBS += -levent -lws2_32

SOURCES += main.cpp \
    RoNet/RoNet.cpp \
    RoNet/private/RoNetMgr.cpp \
    RoNet/private/RoNetUser.cpp \
    SrvUser/SrvUser.cpp \
    SrvUser/SrvUserMgr.cpp \
    ChessServer.cpp \
    SrvConfig/CSrvConfig.cpp \
    SrvConfig/inifile/inifile.cpp \
    Protol/CSProtol.cpp \
    DBThread/DBThreadMgr.cpp \
    DBThread/DBThread.cpp \
    EventBuffer/EventBuffer.cpp \
    EventBuffer/EventBufferRecycle.cpp \
    SrvUser/SrvUser.Event.cpp \
    DBThread/DBThread.Event.cpp \
    ChessGame/Chess/Piece.cpp \
    ChessGame/Chess/Piece.Rules.cpp \
    ChessGame/Chess/Point.cpp \
    ChessGame/ChessGame.cpp \
    ChessGame/ChessGame.Net.cpp \
    DBThread/sqlite/sqlite3.c

include(deployment.pri)
qtcAddDeployment()

HEADERS += \
    RoSpace/RoTypes.h \
    RoNet/RoNet.h \
    RoNet/RoNetTypes.h \
    RoSpace/RoSingleton.h \
    RoNet/private/RoNetMgr.h \
    RoLog/RoLog.h \
    RoSpace/RoTools.h \
    RoNet/private/RoNetUser.h \
    SrvUser/SrvUser.h \
    SrvUser/SrvUserMgr.h \
    ChessServer.h \
    SrvConfig/CSrvConfig.h \
    SrvConfig/inifile/inifile.h \
    Protol/CSProtol.h \
    DBThread/DBThreadMgr.h \
    DBThread/DBThread.h \
    RoSpace/RoThreadPool.h \
    EventBuffer/EventBuffer.h \
    EventBuffer/EventBufferRecycle.h \
    Protol/CSProtol.Serialize.hpp \
    Protol/CSProtol.Parser.hpp \
    Protol/Common.h \
    Protol/CSProtol.SendData.hpp \
    Protol/ServerInternal.h \
    ChessGame/Chess/Piece.h \
    ChessGame/Chess/Point.h \
    ChessGame/ChessGame.h \
    cereal/archives/adapters.hpp \
    cereal/archives/binary.hpp \
    cereal/archives/json.hpp \
    cereal/archives/portable_binary.hpp \
    cereal/archives/xml.hpp \
    cereal/details/helpers.hpp \
    cereal/details/polymorphic_impl.hpp \
    cereal/details/static_object.hpp \
    cereal/details/traits.hpp \
    cereal/details/util.hpp \
    cereal/external/rapidjson/internal/pow10.h \
    cereal/external/rapidjson/internal/stack.h \
    cereal/external/rapidjson/internal/strfunc.h \
    cereal/external/rapidjson/document.h \
    cereal/external/rapidjson/filestream.h \
    cereal/external/rapidjson/genericstream.h \
    cereal/external/rapidjson/prettywriter.h \
    cereal/external/rapidjson/rapidjson.h \
    cereal/external/rapidjson/reader.h \
    cereal/external/rapidjson/stringbuffer.h \
    cereal/external/rapidjson/writer.h \
    cereal/external/rapidxml/rapidxml.hpp \
    cereal/external/rapidxml/rapidxml_iterators.hpp \
    cereal/external/rapidxml/rapidxml_print.hpp \
    cereal/external/rapidxml/rapidxml_utils.hpp \
    cereal/external/base64.hpp \
    cereal/types/array.hpp \
    cereal/types/base_class.hpp \
    cereal/types/bitset.hpp \
    cereal/types/boost_variant.hpp \
    cereal/types/chrono.hpp \
    cereal/types/common.hpp \
    cereal/types/complex.hpp \
    cereal/types/deque.hpp \
    cereal/types/forward_list.hpp \
    cereal/types/list.hpp \
    cereal/types/map.hpp \
    cereal/types/memory.hpp \
    cereal/types/polymorphic.hpp \
    cereal/types/queue.hpp \
    cereal/types/set.hpp \
    cereal/types/stack.hpp \
    cereal/types/string.hpp \
    cereal/types/tuple.hpp \
    cereal/types/unordered_map.hpp \
    cereal/types/unordered_set.hpp \
    cereal/types/utility.hpp \
    cereal/types/valarray.hpp \
    cereal/types/vector.hpp \
    cereal/access.hpp \
    cereal/cereal.hpp \
    cereal/macros.hpp \
    DBThread/sqlite/sqlite3.h

DISTFILES += \
    cereal/external/rapidxml/manual.html \
    cereal/external/rapidjson/license.txt \
    cereal/external/rapidxml/license.txt \
    config-files/chess_config.ini \
    config-files/chess.sql

