# $FreeBSD: head/Mk/Uses/blaslapack.mk 399326 2015-10-15 07:36:38Z bapt $
#
# Handle dependencies on Blas / Lapack
#
# Feature:	blaslapack
# Usage:	USES=blaslapack or USES=blaslapack:ARGS
# Valid ARGS:	atlas netlib gotoblas openblas (default)
#
# Provides:	BLASLIB and LAPACKLIB
#
# Maintainer:	thierry@FreeBSD.org

.if !defined(_INCLUDE_USES_BLASLAPACK_MK)
_INCLUDE_USES_BLASLAPACK_MK=	yes

_valid_ARGS=	atlas gotoblas netlib openblas

_DEFAULT_BLASLAPACK=	netlib

.if empty(blaslapack_ARGS)
blaslapack_ARGS=	${_DEFAULT_BLASLAPACK}
.endif

LDFLAGS+=	-L${LOCALBASE}/lib

.if ${blaslapack_ARGS} == atlas
LIB_DEPENDS+=	libatlas.so:${PORTSDIR}/math/atlas
_BLASLIB=	ptf77blas
LAPACKLIB=	-lalapack -lptcblas
_ATLASLIB=	atlas
ATLASLIB=	-l${_ATLASLIB}
.elif ${blaslapack_ARGS} == gotoblas
LIB_DEPENDS+=	libgoto2.so:${PORTSDIR}/math/gotoblas
LIB_DEPENDS+=	liblapack.so:${PORTSDIR}/math/lapack
_BLASLIB=	goto2p
LAPACKLIB=	-lgoto2p
.elif ${blaslapack_ARGS} == netlib
LIB_DEPENDS+=	libblas.so:${PORTSDIR}/math/blas
LIB_DEPENDS+=	liblapack.so:${PORTSDIR}/math/lapack
_BLASLIB=	blas
LAPACKLIB=	-llapack
.elif ${blaslapack_ARGS} == openblas
LIB_DEPENDS+=	libopenblas.so:${PORTSDIR}/math/openblas
_BLASLIB=	openblasp
LAPACKLIB=	-lopenblasp
.else
IGNORE=		USES=blaslapack: invalid arguments: ${blaslapack_ARGS}
.endif

BLASLIB=	-l${_BLASLIB}

.endif
