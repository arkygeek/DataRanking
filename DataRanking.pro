# -------------------------------------------------------------------
#  REMEMBER TO SET SYSTEM ENVIRONMENT in Projects
#  Variable: DYLD_LIBRARY_PATH
#  Value: /Users/arkygeek/QtProjects/DataRanking/RankPointGenerator
# -------------------------------------------------------------------

TEMPLATE = subdirs
cache()

SUBDIRS += \
    gui \
    RankPointGenerator \
    ModelDetails \
    Scenarios \
    Datasets
