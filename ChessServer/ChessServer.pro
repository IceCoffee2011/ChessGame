TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

QMAKE_CXXFLAGS += -std=c++11
QMAKE_LFLAGS += -levent -lmysqlclient -L/usr/lib64/mysql/ -lpthread
INCLUDEPATH += $$PWD/Protol/

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
    DBThread/Mysql/mysqlquery.cpp \
    EventBuffer/EventBuffer.cpp \
    EventBuffer/EventBufferRecycle.cpp \
    SrvUser/SrvUser.Event.cpp \
    DBThread/DBThread.Event.cpp \
    ChessGame/Chess/Piece.cpp \
    ChessGame/Chess/Piece.Rules.cpp \
    ChessGame/Chess/Point.cpp \
    ChessGame/ChessGame.cpp \
    ChessGame/ChessGame.Net.cpp \
    RoSpace/RoTimer.cpp

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
    DBThread/Mysql/mysqlquery.h \
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
    Protol/cereal/archives/adapters.hpp \
    Protol/cereal/archives/binary.hpp \
    Protol/cereal/archives/json.hpp \
    Protol/cereal/archives/portable_binary.hpp \
    Protol/cereal/archives/xml.hpp \
    Protol/cereal/details/helpers.hpp \
    Protol/cereal/details/polymorphic_impl.hpp \
    Protol/cereal/details/static_object.hpp \
    Protol/cereal/details/traits.hpp \
    Protol/cereal/details/util.hpp \
    Protol/cereal/external/rapidjson/internal/pow10.h \
    Protol/cereal/external/rapidjson/internal/stack.h \
    Protol/cereal/external/rapidjson/internal/strfunc.h \
    Protol/cereal/external/rapidjson/document.h \
    Protol/cereal/external/rapidjson/filestream.h \
    Protol/cereal/external/rapidjson/genericstream.h \
    Protol/cereal/external/rapidjson/prettywriter.h \
    Protol/cereal/external/rapidjson/rapidjson.h \
    Protol/cereal/external/rapidjson/reader.h \
    Protol/cereal/external/rapidjson/stringbuffer.h \
    Protol/cereal/external/rapidjson/writer.h \
    Protol/cereal/external/rapidxml/rapidxml.hpp \
    Protol/cereal/external/rapidxml/rapidxml_iterators.hpp \
    Protol/cereal/external/rapidxml/rapidxml_print.hpp \
    Protol/cereal/external/rapidxml/rapidxml_utils.hpp \
    Protol/cereal/external/base64.hpp \
    Protol/cereal/types/array.hpp \
    Protol/cereal/types/base_class.hpp \
    Protol/cereal/types/bitset.hpp \
    Protol/cereal/types/boost_variant.hpp \
    Protol/cereal/types/chrono.hpp \
    Protol/cereal/types/common.hpp \
    Protol/cereal/types/complex.hpp \
    Protol/cereal/types/deque.hpp \
    Protol/cereal/types/forward_list.hpp \
    Protol/cereal/types/list.hpp \
    Protol/cereal/types/map.hpp \
    Protol/cereal/types/memory.hpp \
    Protol/cereal/types/polymorphic.hpp \
    Protol/cereal/types/queue.hpp \
    Protol/cereal/types/set.hpp \
    Protol/cereal/types/stack.hpp \
    Protol/cereal/types/string.hpp \
    Protol/cereal/types/tuple.hpp \
    Protol/cereal/types/unordered_map.hpp \
    Protol/cereal/types/unordered_set.hpp \
    Protol/cereal/types/utility.hpp \
    Protol/cereal/types/valarray.hpp \
    Protol/cereal/types/vector.hpp \
    Protol/cereal/access.hpp \
    Protol/cereal/cereal.hpp \
    Protol/cereal/macros.hpp \
    RoSpace/RoTimer.h

DISTFILES += \
    Protol/cereal/external/rapidxml/manual.html \
    Protol/cereal/external/rapidjson/license.txt \
    Protol/cereal/external/rapidxml/license.txt

