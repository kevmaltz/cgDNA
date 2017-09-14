#include "Main.h"


void helpExit() {
  cout << "cgDNA -p [DNA PDB]" << endl;
  exit(0);
}


void parsePDB(string *pdbFilename) {
  string buffer, linebuffer;
  int atomid = 0;
  string name;
  double mass, charge, radius;
  vertex crd;
  vector<vertex> coordinates;
  int natoms = 0;

  string atomtype;
  int resid = 0;
  char basetype;
  int basecount = 0;
  double basecoords[3] = {0., 0., 0.};
  int sugcount = 0;
  double sugcoords[3] = {0., 0., 0.};

  ifstream fd(pdbFilename->c_str());

  while(getline(fd, buffer)) {
    if(buffer.compare(0, 4, "ATOM") == 0) {
      bool printBead = false;
      atomtype = buffer.substr(13, 3);
      atomtype = trim(atomtype);

      if(stoi(buffer.substr(25,1)) != resid) {
        resid = stoi(buffer.substr(25,1));
        basetype = buffer[18];
        sugcoords[0] = sugcoords[1] = sugcoords[2] = 0.;
        sugcount = 0;
        basecoords[0] = basecoords[1] = basecoords[2] = 0.;
        basecount = 0;
      }

      if((atomtype.compare(0, 3, "C1'") == 0) or 
         (atomtype.compare(0, 3, "C2'") == 0) or 
         (atomtype.compare(0, 3, "C3'") == 0) or 
         (atomtype.compare(0, 3, "C4'") == 0) or 
         (atomtype.compare(0, 3, "O4'") == 0)) {
        linebuffer = buffer.substr(30, 8);
        sugcoords[0] += stod(linebuffer);
        linebuffer = buffer.substr(38, 8);
        sugcoords[1] += stod(linebuffer);
        linebuffer = buffer.substr(46, 8);
        sugcoords[2] += stod(linebuffer);
        sugcount++;
        if(sugcount == 5) {
          sugcoords[0] /= 5;
          sugcoords[1] /= 5;
          sugcoords[2] /= 5;
          crd.x = sugcoords[0];
          crd.y = sugcoords[1];
          crd.z = sugcoords[2];

          name = "S";
          mass = 83.11;
          charge = -1.;
          radius = 3.5;
          printBead = true;
        }
      } else if(atomtype.length() == 2 or atomtype.compare(0, 3, "C5M") == 0) {
        linebuffer = buffer.substr(30, 8);
        basecoords[0] += stod(linebuffer);
        linebuffer = buffer.substr(38, 8);
        basecoords[1] += stod(linebuffer);
        linebuffer = buffer.substr(46, 8);
        basecoords[2] += stod(linebuffer);
        basecount++;
        if((basetype == 'A' && basecount == 10) or
           (basetype == 'G' && basecount == 11) or
           (basetype == 'C' && basecount ==  8) or
           (basetype == 'T' && basecount ==  9)) {
          basecoords[0] /= basecount;
          basecoords[1] /= basecount;
          basecoords[2] /= basecount;
          crd.x = basecoords[0];
          crd.y = basecoords[1];
          crd.z = basecoords[2];

          name = basetype;
          name.append("b");
          if(basetype == 'A') { mass = 134.1; radius = 4.0; }
          if(basetype == 'G') { mass = 150.1; radius = 4.0; }
          if(basetype == 'T') { mass = 125.1; radius = 3.7; }
          if(basetype == 'C') { mass = 110.1; radius = 3.7; }
          charge = 0.;
          printBead = true;
        }
      }

      if(printBead) {
        natoms++;
        coordinates.push_back(crd);

        cout << "particle ";
        cout.width(10);
        cout.precision(4);
        cout << fixed << crd.x;
        cout << "  ";
        cout.width(8);
        cout.precision(4);
        cout << fixed << crd.y;
        cout << "  ";
        cout.width(8);
        cout.precision(4);
        cout << fixed << crd.z;
        cout << "  ";
        cout.width(8);
        cout.precision(4);
        cout << fixed << charge;
        cout << "  ";
        cout.width(8);
        cout.precision(4);
        cout << fixed << radius;
        cout << "  ";
        cout.width(8);
        cout.precision(4);
        cout << fixed << mass;
        cout << endl;

      }
    }
  }


  /*
  for(int i=0; i < natoms; i++) {
    vertex crdi = coordinates[i];
    for(int j=i+1; j < natoms; j++) {
      vertex crdj = coordinates[j];
      vertex rij = { crdi.x-crdj.x, crdi.y-crdj.y, crdi.z-crdj.z };
      double lij = sqrt(rij.x*rij.x + rij.y*rij.y + rij.z*rij.z);
      if(lij < 9.) {
        cout << "BOND ";
        cout.width(5);
        cout << fixed << i << "  ";
        cout.width(5);
        cout << fixed << j << "  ";
        cout.width(8);
        cout.precision(3);
        cout << lij << "  ";
        cout.width(8);
        cout.precision(3);
        cout << 200.0 << endl;
      }
    }
  }
  */

}


bool getInputWithFlag( int argc, char **argv, //system arguments prog called
                       char flag,             //flag used to indicate filename
                       string *value)         //pointer to filename variable
{
  bool bopt = false;                //is proper input flag entered?
  //Not sure what these to do, however no longer used in function. 9-12-2017
  //  int opt;
  //  char gopt[2] = { flag, ':' };

  for(int i=1; i < argc; i++) 
  {
    if(argv[i][0] == '-' && argv[i][1] == flag) 
    {
      if(argv[i+1][0] != '-') 
      {
        *value = argv[i+1];
        bopt = true;
        i++;
      }
    }
  }

  return bopt;
}


int main(int argc, char **argv)
{
  string pfn;           //filename of PDB to be parsed and converted to PQR
  string ofn;           //

  // Parse command line arguments
  if(argc < 1)
      helpExit();
  if(! getInputWithFlag(argc, argv, 'p', &pfn))
      helpExit();

  // Parse the PDB file
  parsePDB(&pfn);

  return 0;
}

