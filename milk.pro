TEMPLATE = subdirs

SUBDIRS += \
    libs \
    plugins \
    quick \
    tests \
    app

OTHER_FILES += .qmake.conf \
    features/addmilktypes.prf \
    features/addmilkcalc.prf \
    features/addmilksettings.prf \
    features/addmilkdb.prf \
    features/addmilkhtmlbuilder.prf
