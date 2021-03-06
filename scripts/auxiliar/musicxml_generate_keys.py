#!/usr/bin/env python

notes = "CDEFGAB"
alterations = [-1, 0, 1]

def print_measure (nr, fifth, mode, atts1 = "", atts = "", final = ""):
    print("""    <measure number="%s">
      <attributes>
%s        <key>
          <fifths>%s</fifths>
          <mode>%s</mode>
        </key>
%s      </attributes>
      <note>
        <pitch>
          <step>C</step>
          <octave>4</octave>
        </pitch>
        <duration>2</duration>
        <voice>1</voice>
        <type>half</type>
      </note>
%s    </measure>""" % (nr, atts1, fifth, mode, atts, final))

first_div = """        <divisions>1</divisions>
"""
first_atts = """        <time symbol="common">
          <beats>2</beats>
          <beat-type>4</beat-type>
        </time>
        <clef>
          <sign>G</sign>
          <line>2</line>
        </clef>
"""

final_barline = """      <barline location="right">
        <bar-style>light-heavy</bar-style>
      </barline>
"""

print("""<?xml version="1.0" encoding="UTF-8"?>
<!DOCTYPE score-partwise PUBLIC "-//Recordare//DTD MusicXML 1.0 Partwise//EN"
                                "http://www.musicxml.org/dtds/partwise.dtd">
<score-partwise>
  <movement-title>Different Key signatures</movement-title>
  <identification>
    <miscellaneous>
      <miscellaneous-field name="description">Various key signature: from 11
            flats to 11 sharps (each one first one measure in major, then one
            measure in minor)</miscellaneous-field>
    </miscellaneous>
  </identification>
  <part-list>
    <score-part id="P1">
      <part-name>MusicXML Part</part-name>
    </score-part>
  </part-list>
  <!--=========================================================-->
  <part id="P1">""")

max_range = 11
measure = 0
for fifth in range(-max_range, max_range+1):
    measure += 1
    if fifth == -max_range:
        print_measure (measure, fifth, "major", first_div, first_atts)
    else:
        print_measure (measure, fifth, "major")
    measure += 1
    if fifth == max_range:
        print_measure (measure, fifth, "minor", "", "", final_barline)
    else:
        print_measure (measure, fifth, "minor")


print("""  </part>
</score-partwise>""")
