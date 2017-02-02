from os import getenv

try:
  import ROOT

  # retrieve the root core dir environment variable
  RootCoreDir = getenv ("ROOTCOREDIR")
  try:
    t = ROOT.OptObsEventStore()
  except:
    ROOT.gROOT.ProcessLine(".x $ROOTCOREDIR/scripts/load_packages.C")

  # define some print commands that are available as preprocessor macros in the library

except ImportError as err:
  print(err)

