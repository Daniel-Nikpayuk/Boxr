Boxr
========

This app reads, renders and displays the Boxz Technology under a given navigational perspective.

Specification:

  Boxz Technology:

	context: This technology is meant to model a two-dimensional multimedia story that consists of sequences of
		text, audio, images, and video.
	semiotic: These words are valuable in representing the model: 'text', 'audio', 'image', 'video', 'box', 'base', 'layer',
		'scene', 'palette', 'story', 'position', 'dimension'.
	media: A story is a sequence of scenes. Each scene is decomposed into a stack of layers, each layer contains exactly one box.
		There are four types of boxes: text, audio, image, video. Each box has a position and a dimension relative to the base
		layer. Each base layer has a position and a dimension relative to that of the palette.

  Perspectivz Technology:

	context: A collection of objects.
	semiotic: A tree structure where the number of nodes is greater than or equal to the number of context objects.
	media: A bijective mapping between context objects and semiotic nodes. Such a mapping grafts an hierarchical
		ordering onto the context objects and allows for a way of traversing the objects---of parsing and navigating
		them with respect to a given perspective.

  Geographiz Technology:

	context: A collection of Boxz stories.
	semiotic: A tree structure where the number of nodes is greater than or equal to the number of context objects.
	media: A bijective mapping between context objects and semiotic nodes. Such a mapping grafts an hierarchical
		ordering onto the context objects and allows for a way of traversing the objects---of parsing and navigating
		them with respect to a given perspective.

  Librariz Technology:

	context: A collection of Boxz stories.
	semiotic: A tree structure where the number of nodes is greater than or equal to the number of context objects.
	media: A bijective mapping between context objects and semiotic nodes. Such a mapping grafts an hierarchical
		ordering onto the context objects and allows for a way of traversing the objects---of parsing and navigating
		them with respect to a given perspective.

  Tilz Technology:

	context: Anything suitably interpreted as a "Tile". Each Tile has a relationship with every other Tile called their
		"focal relationship". Such a relationship is of two types: existent, non-existent. The terms are otherwise
		open for reinterpretation.
	semiotic: Anything suitably interpreted as a "Rectangle". It must have a Location and a Dimension and a state of Focus.
		Such a state is of two types: true, false. The terms are otherwise open for reinterpretation.
	media: At any given time exactly one Tile has the Focus. All Tiles have equal rights to become the Focus,
		but there is no guarantee of any immediacy towards that. This is to say the Focus is allowed to change
		but the "next" Focus is dependent on the current Tile and its focal relationship to the other Tiles.
		Movements of Focus are allowed depending on whether they have a predetermined "existent" relationship.

  Boxz Reader (Boxr):

	context: Boxz Technology.

		subcontext: The Boxr navigates preexisting Boxz and presents their content to the user.

			Theoretically, the conext is the collection of all possible Boxz. Within this "geography", Storyboxes are the
			territorial unit. Such stories are navigated individually or by the meta-territories of genre. Within a given
			territory, the trails are the parsing perspectives. The initials and terminals (locations) of the trails are
			the scenes, which are rendered and displayed.

			As scalability of rendering is desired the palette dimension of any given StoryBox is a ratio, intended to fit
			and refit many display architectures. All positions are to be considered two dimensional coordinates and so are
			dimensions. All positions and dimensions will be ratios of one above it: So a base layer's is a ratio of the
			palette's, the box's of its base layer's.
		subsemiotic: To be represented as files with the XML specification tags: <story>, <palette>, <scene>, <layer>, <box>,
			<text>, <audio>, <image>, <video> with attributes 'dimension', 'source', 'x', 'y', 'width', height'.
		submedia: A palette is type of scene, in fact is the "empty scene"---there is only one per story. Similarly a base is the empty
			layer, there being only one per scene.

				<story>
				  <palette dimension="W:H"/>
				  <scene>
				    <base x="1:4" y="0:1" height="1:2"/>
				    <layer>
				      <box x="1:5" y="1:5" width="1:3" height="2:7">
				        <video source="file.mpg"/>
				      </box>
				    </layer>
				    <layer>
				      <box x="1:5" y="1:5" width="1:3" height="2:7">
				        <text color="" source="file.txt"/>
				      </box>
				    </layer>
				    <layer>
				      <box x="" y="" width="" height="">
				        <font family="" italic="" size=""/>
				        <text></text>
				      </box>
				    </layer>
				  </scene>
				  <scene>
				    <layer>
				      <box>
				        <audio source=""/>
				      </box>
				    </layer>
				    <layer>
				      <box x="" y="" width="" height="">
				        <image source=""/>
				      </box>
				    </layer>
				  </scene>
				</story>

	semiotic: Perspective Technology and Library Technology.

		A Boxr does not present the Boxz XML, only its content, and specializes in the additional presentation of perspective.
		For example: "identity" (the natural ordering imposed by XML), "flashcards" (Question and Answer Pairs),
		"linear" (Forwards and Backwards) being a few possible natively supported readings. The Layers are presented
		as visual layers over a given box.

		(Storyteller):

		subcontext: The XML implementation of the Boxz Technology.
		subsemiotic: Incomplete.
		submedia: A linear tree.

		(Flashcarder):

		subcontext: The XML implementation of the Boxz Technology.
		subsemiotic: Incomplete.
		submedia: A n-ary root, with unary branches, end in leaves. Question and Answer. A possible example:

				<perspective>
				  <genre name=""/>
				  <parsing>
				    <group by="2"/>
				    <hop by="2"/>
				    <shuffle enable="true"/>
				  </parsing>
				</perspective>

	media: Tile Technology.

		There will be five Tiles: ViewTile, ParseTile, RenderTile, BoxTile, GenreTile. They are arranged as follows:

				  R
				GBV
				  P

Implementation:

Overview:

The general choice of programming language is Qml/Qt, restricted to v4.8.3. This is so that it is compatible with the Playbook OS as
well as Symbian/Meego. As Qt v5.1.0 is backwards compatible with v4.8.x, and it will be deployable on Android and iOS---not to mention
laptop/desktop OSes such as Windows, Mac, and Linux---the reliance on Qml/Qt then is intended for broad distribution and deployment.

	Tile Technology:

Breakdown:

	media: Clause and Graph representations of how tiles relate to each other in terms of positioning,
			and how each tile maps to each screen and speaker type.

Given the nature of Qml/Qt compilation and deployment, it is best to keep the Qt code seperate from the Qml code:

Qt code acts as a plugin to Qml. Regarding the code, each context/semiotic/media collection within a technology specification
---by its initial design---has its own implemented "mediator" class. Such seperation of classes maintains a modular design.
All mediators after all are compiled in the plugin as seperate loadable modules. Exceptions to this rule are as follows:

If a given context/semiotic/media collection of classes itself forms a technology. In that case the mediator
is deferred to the contexts/semiotics/medias within. As well, if, for a given implementation the technology
cannot be---being impractical to do so---seperated into its modular spaces it is acceptable to have what would
otherwise be seperate mediators within the same technology combined into a joint-mediator.

How do I know how what programming language to use in the implementation: Even though I've decided it already, it should really
only be decided after deciding what hardware you're using. How do you decide what hardware to implement it on? Where in the
specification do you signal that? or interpret it from?

