AUTOMAKE_OPTIONS= foreign

QFVIS_LIBS=@QFVIS_LIBS@
QFVIS_DEPS=@QFVIS_DEPS@
QFVIS_INCS=@QFVIS_INCS@
PTHREAD_LDFLAGS=@PTHREAD_LDFLAGS@
PTHREAD_CFLAGS=@PTHREAD_CFLAGS@

INCLUDES=	-I$(top_srcdir)/include $(QFVIS_INCS) $(PTHREAD_CFLAGS)

bin_PROGRAMS=	qfvis

qfvis_SOURCES=	base-vis.c flow.c options.c qfvis.c soundphs.c

qfvis_LDFLAGS=		$(PTHREAD_LDFLAGS)
qfvis_LDADD=		$(QFVIS_LIBS)
qfvis_DEPENDENCIES=	$(QFVIS_DEPS)
